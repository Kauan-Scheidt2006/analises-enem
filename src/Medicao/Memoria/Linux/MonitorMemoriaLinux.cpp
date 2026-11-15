#include "MonitorMemoriaLinux.h"

#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <limits>

namespace {

constexpr std::uint64_t BYTES_POR_KILOBYTE = 1024;

bool converterKilobytes(
    const std::string& linha,
    std::uint64_t& resultado
) {
    std::istringstream fluxo(linha);

    std::string identificador;
    std::uint64_t valor = 0;
    std::string unidade;

    if (!(fluxo >> identificador >> valor >> unidade)) {
        return false;
    }

    if (unidade != "kB") {
        return false;
    }

    if (valor >
        std::numeric_limits<std::uint64_t>::max()
            / BYTES_POR_KILOBYTE) {
        return false;
    }

    resultado = valor * BYTES_POR_KILOBYTE;

    return true;
}

bool consultarStatus(
    const std::string& identificador,
    std::uint64_t& resultado
) {
    std::ifstream arquivo("/proc/self/status");

    if (!arquivo.is_open()) {
        return false;
    }

    std::string linha;

    while (std::getline(arquivo, linha)) {
        if (linha.rfind(identificador, 0) == 0) {
            return converterKilobytes(linha, resultado);
        }
    }

    return false;
}

bool consultarMemoriaPrivada(
    std::uint64_t& resultado
) {
    std::ifstream arquivo("/proc/self/smaps_rollup");

    if (!arquivo.is_open()) {
        return false;
    }

    std::uint64_t memoriaLimpa = 0;
    std::uint64_t memoriaSuja = 0;

    bool encontrouLimpa = false;
    bool encontrouSuja = false;

    std::string linha;

    while (std::getline(arquivo, linha)) {
        if (linha.rfind("Private_Clean:", 0) == 0) {
            encontrouLimpa = converterKilobytes(
                linha,
                memoriaLimpa
            );
        }
        else if (linha.rfind("Private_Dirty:", 0) == 0) {
            encontrouSuja = converterKilobytes(
                linha,
                memoriaSuja
            );
        }

        if (encontrouLimpa && encontrouSuja) {
            break;
        }
    }

    if (!encontrouLimpa || !encontrouSuja) {
        return false;
    }

    if (memoriaLimpa >
        std::numeric_limits<std::uint64_t>::max() - memoriaSuja) {
        return false;
    }

    resultado = memoriaLimpa + memoriaSuja;

    return true;
}

} // namespace

MemoriaProcesso MonitorMemoriaLinux::consultar() const {
    MemoriaProcesso memoria;

    std::uint64_t valor = 0;

    if (consultarStatus("VmRSS:", valor)) {
        memoria.workingSetBytes = valor;
    }
    else {
        memoria.diagnosticos.emplace_back(
            "Nao foi possivel consultar VmRSS em /proc/self/status."
        );
    }

    if (consultarStatus("VmHWM:", valor)) {
        memoria.peakWorkingSetBytes = valor;
    }
    else {
        memoria.diagnosticos.emplace_back(
            "Nao foi possivel consultar VmHWM em /proc/self/status."
        );
    }

    if (consultarMemoriaPrivada(valor)) {
        memoria.privateUsageBytes = valor;

        memoria.definicaoMemoriaPrivada =
            DefinicaoMemoriaPrivada::MemoriaResidente;
    }
    else {
        memoria.diagnosticos.emplace_back(
            "Nao foi possivel consultar a memoria privada "
            "em /proc/self/smaps_rollup."
        );
    }

    // O Linux nao fornece aqui um pico acumulado equivalente
    // para a memoria privada residente.
    memoria.peakPrivateUsageBytes = std::nullopt;

    return memoria;
}