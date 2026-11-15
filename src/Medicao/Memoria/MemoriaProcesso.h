#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

enum class DefinicaoMemoriaPrivada {
    Indisponivel,
    MemoriaComprometida,
    MemoriaResidente
};

struct MemoriaProcesso {
    // Memória residente atual.
    std::optional<std::uint64_t> workingSetBytes;

    // Memória privada atual.
    std::optional<std::uint64_t> privateUsageBytes;

    // Maior memória residente registrada pelo sistema.
    std::optional<std::uint64_t> peakWorkingSetBytes;

    // Maior memória privada registrada, quando disponível.
    std::optional<std::uint64_t> peakPrivateUsageBytes;

    // Define o significado do indicador de memória privada.
    DefinicaoMemoriaPrivada definicaoMemoriaPrivada =
        DefinicaoMemoriaPrivada::Indisponivel;

    // Diagnósticos de falhas ou indisponibilidade.
    std::vector<std::string> diagnosticos;
};
