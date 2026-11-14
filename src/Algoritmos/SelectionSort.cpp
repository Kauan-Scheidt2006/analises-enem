
#include "Algoritmos/SelectionSort.h"

#include <cstddef>

std::string_view SelectionSort::nome() const noexcept {
    return "Selection Sort";
}

void SelectionSort::ordenarImpl(std::vector<Registro>& registros) {
    const std::size_t tamanho = registros.size();

    for (std::size_t i = 0; i + 1 < tamanho; ++i) {
        std::size_t indiceMenor = i;

        for (std::size_t j = i + 1; j < tamanho; ++j) {
            if (menor(registros[j], registros[indiceMenor])) {
                indiceMenor = j;
            }
        }

        if (indiceMenor != i) {
            trocar(registros[i], registros[indiceMenor]);
        }
    }
}
