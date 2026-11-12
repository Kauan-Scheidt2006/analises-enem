#include "ServicoCenarios.h"

#include <algorithm>
#include <mutex>
#include <random>
#include <stdexcept>
#include <utility>

namespace {

void validarConfiguracao(const ConfiguracaoCenarios& configuracao) {
    for (std::size_t indice = 0; indice < configuracao.tamanhos.size(); ++indice) {
        const std::size_t tamanho = configuracao.tamanhos[indice];

        if (tamanho == 0) {
            throw std::invalid_argument(
                "Os tamanhos dos cenarios devem ser maiores que zero.");
        }

        if (indice > 0 && tamanho <= configuracao.tamanhos[indice - 1]) {
            throw std::invalid_argument(
                "Os tamanhos dos cenarios devem ser unicos e crescentes.");
        }
    }
}

class GeradorCenarios final {
public:
    explicit GeradorCenarios(ConfiguracaoCenarios configuracao)
        : configuracao_(std::move(configuracao)) {}

    [[nodiscard]] ColecaoCenarios gerarTodos(
        const std::vector<Registro>& registros) const {
        validarDataset(registros);

        ColecaoCenarios colecao;
        colecao.reserve(configuracao_.tamanhos.size());

        for (const std::size_t tamanho : configuracao_.tamanhos) {
            colecao.push_back(gerarConjunto(registros, tamanho));
        }

        return colecao;
    }

private:
    void validarDataset(const std::vector<Registro>& registros) const {
        for (const std::size_t tamanho : configuracao_.tamanhos) {
            if (tamanho > registros.size()) {
                throw std::out_of_range(
                    "O dataset nao possui registros suficientes para os cenarios configurados.");
            }
        }
    }

    [[nodiscard]] static std::vector<Registro> gerarAmostra(
        const std::vector<Registro>& registros,
        std::size_t quantidade) {
        return {
            registros.begin(),
            registros.begin() + static_cast<std::ptrdiff_t>(quantidade)
        };
    }

    [[nodiscard]] ConjuntoCenarios gerarConjunto(
        const std::vector<Registro>& registros,
        std::size_t quantidade) const {
        auto ordenado = gerarAmostra(registros, quantidade);
        std::sort(ordenado.begin(), ordenado.end());

        auto reverso = ordenado;
        std::reverse(reverso.begin(), reverso.end());

        auto aleatorio = ordenado;
        std::mt19937 motor(configuracao_.semente);
        std::shuffle(aleatorio.begin(), aleatorio.end(), motor);

        return {
            .tamanho = quantidade,
            .semente = configuracao_.semente,
            .ordenado = std::move(ordenado),
            .reverso = std::move(reverso),
            .aleatorio = std::move(aleatorio)
        };
    }

    ConfiguracaoCenarios configuracao_;
};

class EstadoCenarios final {
public:
    static EstadoCenarios& instancia() {
        static EstadoCenarios instancia;
        return instancia;
    }

    void configurar(ConfiguracaoCenarios configuracao) {
        validarConfiguracao(configuracao);

        std::scoped_lock bloqueio(mutex_);
        if (geracaoIniciada_) {
            throw std::logic_error(
                "A configuracao de cenarios nao pode ser alterada apos o inicio da geracao.");
        }

        if (configurado_) {
            throw std::logic_error(
                "O servico de cenarios pode ser configurado apenas uma vez por execucao.");
        }

        configuracao_ = std::move(configuracao);
        configurado_ = true;
    }

    [[nodiscard]] ConfiguracaoCenarios iniciarGeracao() {
        std::scoped_lock bloqueio(mutex_);
        if (!configurado_) {
            throw std::logic_error(
                "O servico de cenarios deve ser configurado antes da geracao.");
        }

        geracaoIniciada_ = true;
        return configuracao_;
    }

private:
    EstadoCenarios() = default;

    ConfiguracaoCenarios configuracao_{};
    bool configurado_{false};
    bool geracaoIniciada_{false};
    std::mutex mutex_;
};

}  // namespace

const std::vector<Registro>& ConjuntoCenarios::obter(TipoCenario tipo) const {
    switch (tipo) {
    case TipoCenario::Ordenado:
        return ordenado;
    case TipoCenario::Reverso:
        return reverso;
    case TipoCenario::Aleatorio:
        return aleatorio;
    }

    throw std::invalid_argument("Tipo de cenario desconhecido.");
}

void ServicoCenarios::configurar(ConfiguracaoCenarios configuracao) {
    EstadoCenarios::instancia().configurar(std::move(configuracao));
}

ColecaoCenarios ServicoCenarios::gerarTodos(
    const std::vector<Registro>& registros) {
    const ConfiguracaoCenarios configuracao =
        EstadoCenarios::instancia().iniciarGeracao();

    return GeradorCenarios(configuracao).gerarTodos(registros);
}
