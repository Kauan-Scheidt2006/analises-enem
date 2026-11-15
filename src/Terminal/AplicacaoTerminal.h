#pragma once

#include "Registro/Registro.h"
#include "../Resultados/ResultadoExecucao.h"
#include <vector>

class AplicacaoTerminal final {
public:
    explicit AplicacaoTerminal(
        const std::vector<Registro>& registros);

    void executar();

private:
    const std::vector<Registro>& registros_;

    void apresentarCabecalho() const;
    void apresentarResultado(const ResultadoExecucao& resultado) const;
};