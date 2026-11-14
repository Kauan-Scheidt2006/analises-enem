#pragma once

#include "Algoritmos/AlgoritmoOrdenacao.h"

#include <cstddef>

class QuickSort final : public AlgoritmoOrdenacao {
public:
    [[nodiscard]] std::string_view nome() const noexcept override;

private:
    void ordenarImpl(std::vector<Registro>& registros) override;
    void ordenarIntervalo(std::vector<Registro>& registros,
                          std::ptrdiff_t inicio,
                          std::ptrdiff_t fim);
    [[nodiscard]] std::ptrdiff_t particionar(std::vector<Registro>& registros,
                                              std::ptrdiff_t inicio,
                                              std::ptrdiff_t fim);
    [[nodiscard]] std::ptrdiff_t escolherPivoMedianaDeTres(
        const std::vector<Registro>& registros,
        std::ptrdiff_t inicio,
        std::ptrdiff_t fim);
};
