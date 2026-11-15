#pragma once

#include "Registro/Registro.h"
#include "Dominio/Tipos/DisposicaoInicial.h"

#include <cstddef>
#include <cstdint>
#include <vector>

struct ConjuntoCenarios {
    std::size_t quantidade{};
    std::uint32_t semente{};
    DisposicaoInicial disposicao{};

    std::vector<Registro> registros;

    [[nodiscard]] std::vector<Registro>& obter() noexcept;

    [[nodiscard]] const std::vector<Registro>& obter() const noexcept;
};