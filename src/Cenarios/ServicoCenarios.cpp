#include "Cenarios/ServicoCenarios.h"

#include <algorithm>
#include <random>
#include <stdexcept>

ConjuntoCenarios ServicoCenarios::gerar(
    const std::vector<Registro>& registros,
    std::size_t quantidade,
    DisposicaoInicial disposicao,
    std::uint32_t semente) {

    if (quantidade == 0 || quantidade > registros.size()) {
        throw std::invalid_argument(
            "Quantidade de registros inválida.");
    }

    ConjuntoCenarios conjunto;

    conjunto.quantidade = quantidade;
    conjunto.semente = semente;
    conjunto.disposicao = disposicao;

    // Seleciona somente os primeiros N registros.
    conjunto.registros.assign(
        registros.begin(),
        registros.begin() + quantidade);

    switch (disposicao) {
    case DisposicaoInicial::Ordenada:
        std::sort(
            conjunto.registros.begin(),
            conjunto.registros.end());
        break;

    case DisposicaoInicial::Reversa:
        std::sort(
            conjunto.registros.begin(),
            conjunto.registros.end());

        std::reverse(
            conjunto.registros.begin(),
            conjunto.registros.end());
        break;

    case DisposicaoInicial::Aleatoria: {
        std::mt19937 gerador(semente);

        std::shuffle(
            conjunto.registros.begin(),
            conjunto.registros.end(),
            gerador);
        break;
    }

    default:
        throw std::invalid_argument(
            "Disposição inicial inválida.");
    }

    return conjunto;
}