#pragma once

#include "../Registro/Registro.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

enum class TipoCenario {
    Ordenado,
    Reverso,
    Aleatorio
};

struct ConfiguracaoCenarios {
    std::uint32_t semente{42};
    std::array<std::size_t, 3> tamanhos{
        10'000,
        100'000,
        1'000'000
    };
};

struct ConjuntoCenarios {
    std::size_t tamanho{};
    std::uint32_t semente{};

    std::vector<Registro> ordenado;
    std::vector<Registro> reverso;
    std::vector<Registro> aleatorio;

    [[nodiscard]] const std::vector<Registro>& obter(
        TipoCenario tipo) const;
};

using ColecaoCenarios = std::vector<ConjuntoCenarios>;

class ServicoCenarios final {
public:
    ServicoCenarios() = delete;

    static void configurar(ConfiguracaoCenarios configuracao);

    [[nodiscard]] static ColecaoCenarios gerarTodos(
        const std::vector<Registro>& registros);
};
