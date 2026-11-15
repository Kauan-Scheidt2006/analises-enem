#pragma once

#include "Cenarios/ConjuntoCenarios.h"

#include <cstddef>
#include <cstdint>
#include <vector>

class ServicoCenarios final {
public:
    [[nodiscard]] static ConjuntoCenarios gerar(
        const std::vector<Registro>& registros,
        std::size_t quantidade,
        DisposicaoInicial disposicao,
        std::uint32_t semente);
};