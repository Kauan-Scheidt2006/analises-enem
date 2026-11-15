#include "ExecutorExperimento.h"

#include "Medicao/Tempo/MedidorTempo.h"

#include <chrono>
#include <cstdint>
#include <exception>
#include <limits>
#include <optional>
#include <string>

namespace {

MemoriaProcesso consultarMemoriaSegura(const MonitorMemoriaProcesso& monitor) {
    try {
        return monitor.consultar();
    }
    catch (const std::exception& erro) {
        MemoriaProcesso memoria;

        memoria.diagnosticos.emplace_back(
            std::string("Falha inesperada na consulta de memoria: ")
            + erro.what()
        );

        return memoria;
    }
    catch (...) {
        MemoriaProcesso memoria;

        memoria.diagnosticos.emplace_back(
            "Falha desconhecida na consulta de memoria."
        );

        return memoria;
    }
}

std::optional<std::int64_t> calcularVariacao(
    const std::optional<std::uint64_t>& inicial,
    const std::optional<std::uint64_t>& final
) {
    if (!inicial || !final) {
        return std::nullopt;
    }

    constexpr auto limite =
        static_cast<std::uint64_t>(
            std::numeric_limits<std::int64_t>::max()
        );

    if (*final >= *inicial) {
        const std::uint64_t diferenca = *final - *inicial;

        if (diferenca > limite) {
            return std::nullopt;
        }

        return static_cast<std::int64_t>(diferenca);
    }

    const std::uint64_t diferenca = *inicial - *final;

    if (diferenca > limite) {
        return std::nullopt;
    }

    return -static_cast<std::int64_t>(diferenca);
}

VariacaoMemoria calcularVariacaoMemoria(
    const MemoriaProcesso& inicial,
    const MemoriaProcesso& final
) {
    VariacaoMemoria variacao;

    variacao.workingSetBytes = calcularVariacao(
        inicial.workingSetBytes,
        final.workingSetBytes
    );

    variacao.privateUsageBytes = calcularVariacao(
        inicial.privateUsageBytes,
        final.privateUsageBytes
    );

    return variacao;
}

} // namespace

ExecutorExperimento::ExecutorExperimento(
    MonitorMemoriaProcesso& monitorMemoria
) noexcept
    : monitorMemoria_(monitorMemoria) {
}

ResultadoExecucao ExecutorExperimento::executar(
    AlgoritmoOrdenacao& algoritmo,
    std::vector<Registro>& registros
) const {

    ResultadoExecucao resultado;

    // Identificação do algoritmo.
    resultado.nomeAlgoritmo = std::string(algoritmo.nome());

    // 1. Fotografia inicial da memória.
    resultado.memoriaInicial =
        consultarMemoriaSegura(monitorMemoria_);

    // 2. Medição exclusiva da ordenação.
    {
        MedidorTempo::Escopo medicao(
            resultado.tempoOrdenacao
        );

        algoritmo.ordenar(registros);
    }

    // 3. Fotografia final da memória.
    resultado.memoriaFinal =
        consultarMemoriaSegura(monitorMemoria_);

    // 4. Coleta dos contadores do algoritmo.
    resultado.comparacoes = algoritmo.comparacoes();

    resultado.movimentacoes = algoritmo.movimentacoes();

    // 5. Cálculo das variações entre as fotografias.
    resultado.variacaoMemoria = calcularVariacaoMemoria(
        resultado.memoriaInicial,
        resultado.memoriaFinal
    );

    return resultado;
}