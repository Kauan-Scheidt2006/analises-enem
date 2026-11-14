#include "Algoritmos/MergeSort.h"

#include <algorithm>
#include <utility>

std::string_view MergeSort::nome() const noexcept {
    return "MergeSort";
}

void MergeSort::ordenarImpl(std::vector<Registro>& registros) {
    const std::size_t quantidade = registros.size();

    if (quantidade < 2) {
        return;
    }

    // O vetor auxiliar e alocado uma unica vez e liberado automaticamente
    // ao termino da ordenacao.
    std::vector<Registro> auxiliar(quantidade);

    std::vector<Registro>* origem = &registros;
    std::vector<Registro>* destino = &auxiliar;
    std::size_t largura = 1;

    while (largura < quantidade) {
        std::size_t inicio = 0;

        while (inicio < quantidade) {
            const std::size_t meio =
                inicio + std::min(largura, quantidade - inicio);
            const std::size_t fim =
                meio + std::min(largura, quantidade - meio);

            intercalar(*origem, *destino, inicio, meio, fim);

            if (fim == quantidade) {
                break;
            }

            inicio = fim;
        }

        using std::swap;
        swap(origem, destino);

        if (largura > quantidade / 2) {
            break;
        }

        largura *= 2;
    }

    if (origem != &registros) {
        copiarIntervalo(*origem, registros, 0, quantidade);
    }
}

void MergeSort::intercalar(const std::vector<Registro>& origem,
                           std::vector<Registro>& destino,
                           std::size_t inicio,
                           std::size_t meio,
                           std::size_t fim) {
    std::size_t esquerda = inicio;
    std::size_t direita = meio;
    std::size_t posicaoDestino = inicio;

    while (esquerda < meio && direita < fim) {
        // Em caso de chaves iguais, preserva a ordem relativa da entrada.
        if (menor(origem[direita], origem[esquerda])) {
            destino[posicaoDestino] = origem[direita];
            ++direita;
        } else {
            destino[posicaoDestino] = origem[esquerda];
            ++esquerda;
        }

        ++posicaoDestino;
        registrarMovimentacao();
    }

    while (esquerda < meio) {
        destino[posicaoDestino] = origem[esquerda];
        ++esquerda;
        ++posicaoDestino;
        registrarMovimentacao();
    }

    while (direita < fim) {
        destino[posicaoDestino] = origem[direita];
        ++direita;
        ++posicaoDestino;
        registrarMovimentacao();
    }
}

void MergeSort::copiarIntervalo(const std::vector<Registro>& origem,
                                std::vector<Registro>& destino,
                                std::size_t inicio,
                                std::size_t fim) {
    for (std::size_t indice = inicio; indice < fim; ++indice) {
        destino[indice] = origem[indice];
        registrarMovimentacao();
    }
}
