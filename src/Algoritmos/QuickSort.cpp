#include "Algoritmos/QuickSort.h"

#include <utility>

std::string_view QuickSort::nome() const noexcept {
    return "QuickSort";
}

void QuickSort::ordenarImpl(std::vector<Registro>& registros) {
    if (registros.size() < 2) {
        return;
    }

    ordenarIntervalo(registros, 0,
                     static_cast<std::ptrdiff_t>(registros.size()) - 1);
}

void QuickSort::ordenarIntervalo(std::vector<Registro>& registros,
                                 std::ptrdiff_t inicio,
                                 std::ptrdiff_t fim) {
    while (inicio < fim) {
        const std::ptrdiff_t divisao = particionar(registros, inicio, fim);
        const std::ptrdiff_t tamanhoEsquerda = divisao - inicio + 1;
        const std::ptrdiff_t tamanhoDireita = fim - divisao;

        if (tamanhoEsquerda <= tamanhoDireita) {
            ordenarIntervalo(registros, inicio, divisao);
            inicio = divisao + 1;
        } else {
            ordenarIntervalo(registros, divisao + 1, fim);
            fim = divisao;
        }
    }
}

std::ptrdiff_t QuickSort::particionar(std::vector<Registro>& registros,
                                      std::ptrdiff_t inicio,
                                      std::ptrdiff_t fim) {
    const std::ptrdiff_t indicePivo = escolherPivoMedianaDeTres(
        registros, inicio, fim);
    const Registro pivo = registros[static_cast<std::size_t>(indicePivo)];
    registrarMovimentacao();

    std::ptrdiff_t esquerda = inicio;
    std::ptrdiff_t direita = fim;

    while (true) {
        while (menor(registros[static_cast<std::size_t>(esquerda)], pivo)) {
            ++esquerda;
        }

        while (menor(pivo, registros[static_cast<std::size_t>(direita)])) {
            --direita;
        }

        if (esquerda >= direita) {
            return direita;
        }

        trocar(registros[static_cast<std::size_t>(esquerda)],
               registros[static_cast<std::size_t>(direita)]);
        ++esquerda;
        --direita;
    }
}

std::ptrdiff_t QuickSort::escolherPivoMedianaDeTres(
    const std::vector<Registro>& registros,
    std::ptrdiff_t inicio,
    std::ptrdiff_t fim) {
    const std::ptrdiff_t meio = inicio + (fim - inicio) / 2;
    const Registro& primeiro = registros[static_cast<std::size_t>(inicio)];
    const Registro& central = registros[static_cast<std::size_t>(meio)];
    const Registro& ultimo = registros[static_cast<std::size_t>(fim)];

    if (menor(primeiro, central)) {
        if (menor(central, ultimo)) {
            return meio;
        }

        return menor(primeiro, ultimo) ? fim : inicio;
    }

    if (menor(primeiro, ultimo)) {
        return inicio;
    }

    return menor(central, ultimo) ? fim : meio;
}
