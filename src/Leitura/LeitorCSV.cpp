#include "LeitorCSV.h"
#include <charconv>
#include <fstream>
#include <stdexcept>
#include <system_error>
#include <utility>

namespace {

void removerRetornoDeCarro(std::string& texto) {
    if (!texto.empty() && texto.back() == '\r') {
        texto.pop_back();
    }
}

std::vector<std::string> separarCampos(const std::string& linha, char delimitador) {
    std::vector<std::string> campos;
    std::size_t inicio = 0;

    while (true) {
        const std::size_t fim = linha.find(delimitador, inicio);
        if (fim == std::string::npos) {
            campos.emplace_back(linha.substr(inicio));
            break;
        }

        campos.emplace_back(linha.substr(inicio, fim - inicio));
        inicio = fim + 1;
    }

    return campos;
}

}  // namespace

LeitorCSV::LeitorCSV(ConfiguracaoCSV configuracao)
    : configuracao_(std::move(configuracao)) {
    if (configuracao_.colunaInscricao.empty()) {
        throw std::invalid_argument("O nome da coluna de inscricao nao pode ser vazio.");
    }

    if (configuracao_.delimitador == '\0' ||
        configuracao_.delimitador == '\n' ||
        configuracao_.delimitador == '\r') {
        throw std::invalid_argument("O delimitador configurado e invalido.");
    }
}

std::vector<Registro> LeitorCSV::carregar(
    const std::filesystem::path& caminho) const {
    std::ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        throw std::runtime_error(
            "Nao foi possivel abrir o arquivo: " + caminho.string());
    }

    std::vector<Registro> registros;
    std::string linha;
    std::size_t numeroLinha = 0;
    std::size_t indiceColuna = 0;

    if (configuracao_.possuiCabecalho) {
        if (!std::getline(arquivo, linha)) {
            throw std::runtime_error(
                "O arquivo esta vazio: " + caminho.string());
        }

        ++numeroLinha;
        removerRetornoDeCarro(linha);
        indiceColuna = localizarColunaInscricao(linha);
    }

    while (std::getline(arquivo, linha)) {
        ++numeroLinha;
        removerRetornoDeCarro(linha);

        try {
            registros.push_back(
                converterLinha(linha, indiceColuna, numeroLinha));
        } catch (const std::runtime_error& erro) {
            if (configuracao_.politica == PoliticaLinhaInvalida::Interromper) {
                throw std::runtime_error(
                    "Erro ao ler \"" + caminho.string() + "\": " + erro.what());
            }
        }
    }

    if (arquivo.bad()) {
        throw std::runtime_error(
            "Falha durante a leitura do arquivo: " + caminho.string());
    }

    return registros;
}

std::size_t LeitorCSV::localizarColunaInscricao(
    const std::string& cabecalho) const {
    if (cabecalho.empty()) {
        throw std::runtime_error("O cabecalho do arquivo esta vazio.");
    }

    const auto colunas = separarCampos(cabecalho, configuracao_.delimitador);
    for (std::size_t indice = 0; indice < colunas.size(); ++indice) {
        if (colunas[indice] == configuracao_.colunaInscricao) {
            return indice;
        }
    }

    throw std::runtime_error(
        "Coluna obrigatoria nao encontrada: " + configuracao_.colunaInscricao);
}

Registro LeitorCSV::converterLinha(
    const std::string& linha,
    std::size_t indiceColuna,
    std::size_t numeroLinha) const {
    if (linha.empty()) {
        throw std::runtime_error(
            "linha " + std::to_string(numeroLinha) + " esta vazia.");
    }

    const auto campos = separarCampos(linha, configuracao_.delimitador);
    if (indiceColuna >= campos.size()) {
        throw std::runtime_error(
            "linha " + std::to_string(numeroLinha) +
            " nao possui a coluna " + configuracao_.colunaInscricao + ".");
    }

    const std::string& campo = campos[indiceColuna];
    if (campo.empty()) {
        throw std::runtime_error(
            "linha " + std::to_string(numeroLinha) +
            " possui valor vazio para " + configuracao_.colunaInscricao + ".");
    }

    std::uint64_t inscricao = 0;
    const char* inicio = campo.data();
    const char* fim = inicio + campo.size();
    const auto resultado = std::from_chars(inicio, fim, inscricao);

    if (resultado.ec == std::errc::result_out_of_range) {
        throw std::runtime_error(
            "linha " + std::to_string(numeroLinha) +
            " possui valor fora da faixa para " + configuracao_.colunaInscricao +
            ": \"" + campo + "\".");
    }

    if (resultado.ec != std::errc{} || resultado.ptr != fim) {
        throw std::runtime_error(
            "linha " + std::to_string(numeroLinha) +
            " possui valor invalido para " + configuracao_.colunaInscricao +
            ": \"" + campo + "\".");
    }

    return Registro{inscricao};
}
