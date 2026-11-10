#pragma once

#include "../Registro/Registro.h"

#include <filesystem>
#include <string>
#include <vector>

enum class PoliticaLinhaInvalida {
    Interromper,
    Ignorar
};

struct ConfiguracaoCSV {
    std::string colunaInscricao{"NU_INSCRICAO"};
    char delimitador{','};
    bool possuiCabecalho{true};
    PoliticaLinhaInvalida politica{PoliticaLinhaInvalida::Interromper};
};

class LeitorCSV final {
public:
    explicit LeitorCSV(ConfiguracaoCSV configuracao = {});

    [[nodiscard]] std::vector<Registro> carregar(
        const std::filesystem::path& caminho) const;

private:
    [[nodiscard]] std::size_t localizarColunaInscricao(
        const std::string& cabecalho) const;

    [[nodiscard]] Registro converterLinha(
        const std::string& linha,
        std::size_t indiceColuna,
        std::size_t numeroLinha) const;

    ConfiguracaoCSV configuracao_;
};
