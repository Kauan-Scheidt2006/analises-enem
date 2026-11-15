
#pragma once

#include "Algoritmos/AlgoritmoOrdenacao.h"

class SelectionSort final : public AlgoritmoOrdenacao {
public:
    [[nodiscard]] std::string_view nome() const noexcept override;

private:
    void ordenarImpl(std::vector<Registro>& registros) override;
};
