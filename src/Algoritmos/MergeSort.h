#pragma once

#include "Algoritmos/AlgoritmoOrdenacao.h"

#include <cstddef>
#include <vector>

class MergeSort final : public AlgoritmoOrdenacao {
public:
    [[nodiscard]] std::string_view nome() const noexcept override;

private:
    void ordenarImpl(std::vector<Registro>& registros) override;

    void intercalar(const std::vector<Registro>& origem,
                    std::vector<Registro>& destino,
                    std::size_t inicio,
                    std::size_t meio,
                    std::size_t fim);

    void copiarIntervalo(const std::vector<Registro>& origem,
                         std::vector<Registro>& destino,
                         std::size_t inicio,
                         std::size_t fim);
};
