#pragma once

#include "Algoritmos/AlgoritmoOrdenacao.h"
#include "Dominio/Tipos/TipoAlgoritmo.h"

#include <memory>
#include <string_view>

class CatalogoAlgoritmos final {
public:
    [[nodiscard]] static std::unique_ptr<AlgoritmoOrdenacao>
    criar(TipoAlgoritmo tipo);

    [[nodiscard]] static std::string_view
    nome(TipoAlgoritmo tipo) noexcept;
};