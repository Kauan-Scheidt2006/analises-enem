#pragma once

#include "Registro/Registro.h"

#include <cstdint>
#include <string_view>
#include <vector>

class AlgoritmoOrdenacao {
public:
    virtual ~AlgoritmoOrdenacao() = default;

    void ordenar(std::vector<Registro>& registros);

    [[nodiscard]] virtual std::string_view nome() const noexcept = 0;
    [[nodiscard]] std::uint64_t comparacoes() const noexcept;
    [[nodiscard]] std::uint64_t movimentacoes() const noexcept;

protected:
    // Uma comparação entre duas chaves é contabilizada a cada chamada.
    [[nodiscard]] bool menor(const Registro& esquerdo,
                             const Registro& direito) noexcept;

    // Uma troca é contabilizada como três movimentações: cópia temporária e
    // as duas atribuições aos elementos do vetor.
    void trocar(Registro& esquerdo, Registro& direito) noexcept;
    void registrarMovimentacao(std::uint64_t quantidade = 1) noexcept;

private:
    virtual void ordenarImpl(std::vector<Registro>& registros) = 0;
    void resetarContadores() noexcept;

    std::uint64_t comparacoes_{};
    std::uint64_t movimentacoes_{};
};
