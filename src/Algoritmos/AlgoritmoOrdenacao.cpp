#include "Algoritmos/AlgoritmoOrdenacao.h"

#include <utility>

void AlgoritmoOrdenacao::ordenar(std::vector<Registro>& registros) {
    resetarContadores();
    ordenarImpl(registros);
}

std::uint64_t AlgoritmoOrdenacao::comparacoes() const noexcept {
    return comparacoes_;
}

std::uint64_t AlgoritmoOrdenacao::movimentacoes() const noexcept {
    return movimentacoes_;
}

bool AlgoritmoOrdenacao::menor(const Registro& esquerdo,
                                const Registro& direito) noexcept {
    ++comparacoes_;
    return esquerdo < direito;
}

void AlgoritmoOrdenacao::trocar(Registro& esquerdo, Registro& direito) noexcept {
    if (&esquerdo == &direito) {
        return;
    }

    using std::swap;
    swap(esquerdo, direito);
    movimentacoes_ += 3;
}

void AlgoritmoOrdenacao::registrarMovimentacao(std::uint64_t quantidade) noexcept {
    movimentacoes_ += quantidade;
}

void AlgoritmoOrdenacao::resetarContadores() noexcept {
    comparacoes_ = 0;
    movimentacoes_ = 0;
}
