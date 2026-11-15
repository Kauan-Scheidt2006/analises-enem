#pragma once
#include "../Medicao/Memoria/MemoriaProcesso.h"

#include <chrono>
#include <cstdint>
#include <optional>
#include <string>

struct VariacaoMemoria {
    std::optional<std::int64_t> workingSetBytes;
    std::optional<std::int64_t> privateUsageBytes;
};

struct ResultadoExecucao {
    std::string nomeAlgoritmo;

    std::uint64_t comparacoes = 0;
    std::uint64_t movimentacoes = 0;

    std::chrono::nanoseconds tempoOrdenacao{0};

    MemoriaProcesso memoriaInicial;
    MemoriaProcesso memoriaFinal;

    VariacaoMemoria variacaoMemoria;
};
