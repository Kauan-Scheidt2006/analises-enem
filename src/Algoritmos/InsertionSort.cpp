
#include "Algoritmos/InsertionSort.h"

#include <cstddef>

std::string_view InsertionSort::nome() const noexcept {
    return "Insertion Sort";
}

void InsertionSort::ordenarImpl(std::vector<Registro>& registros) {
    const std::size_t tamanho = registros.size();

    for (std::size_t i = 1; i < tamanho; ++i) {
        Registro atual = registros[i];

        std::size_t j = i;

        while (j > 0 && menor(atual, registros[j - 1])) {
            registros[j] = registros[j - 1];
            registrarMovimentacao();

            --j;
        }

        if (j != i) {
            registros[j] = atual;
            registrarMovimentacao();
        }
    }
}
