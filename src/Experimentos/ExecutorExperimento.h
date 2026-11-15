#pragma once

#include "Algoritmos/AlgoritmoOrdenacao.h"
#include "Medicao/Memoria/MonitorMemoriaProcesso.h"
#include "Resultados/ResultadoExecucao.h"

#include <vector>

class ExecutorExperimento {
public:
    explicit ExecutorExperimento(
        MonitorMemoriaProcesso& monitorMemoria
    ) noexcept;

    ResultadoExecucao executar(
        AlgoritmoOrdenacao& algoritmo,
        std::vector<Registro>& registros
    ) const;

private:
    MonitorMemoriaProcesso& monitorMemoria_;
};

