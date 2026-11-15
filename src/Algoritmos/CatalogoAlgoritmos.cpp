
#include "Algoritmos/CatalogoAlgoritmos.h"

#include "Algoritmos/SelectionSort.h"
#include "Algoritmos/InsertionSort.h"
#include "Algoritmos/MergeSort.h"
#include "Algoritmos/QuickSort.h"

#include <stdexcept>

std::unique_ptr<AlgoritmoOrdenacao>
CatalogoAlgoritmos::criar(TipoAlgoritmo tipo) {
    switch (tipo) {
    case TipoAlgoritmo::SelectionSort:
        return std::make_unique<SelectionSort>();

    case TipoAlgoritmo::InsertionSort:
        return std::make_unique<InsertionSort>();

    case TipoAlgoritmo::MergeSort:
        return std::make_unique<MergeSort>();

    case TipoAlgoritmo::QuickSort:
        return std::make_unique<QuickSort>();
    }

    throw std::invalid_argument("Tipo de algoritmo inválido.");
}

std::string_view
CatalogoAlgoritmos::nome(TipoAlgoritmo tipo) noexcept {
    switch (tipo) {
    case TipoAlgoritmo::SelectionSort:
        return "Selection Sort";

    case TipoAlgoritmo::InsertionSort:
        return "Insertion Sort";

    case TipoAlgoritmo::MergeSort:
        return "Merge Sort";

    case TipoAlgoritmo::QuickSort:
        return "Quick Sort";
    }

    return "Desconhecido";
}
