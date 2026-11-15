#include "Terminal/AplicacaoTerminal.h"
#include "../Medicao/Memoria/CriadorMonitorMemoria.h"
#include "Algoritmos/AlgoritmoOrdenacao.h"
#include "Algoritmos/CatalogoAlgoritmos.h"
#include "Cenarios/ServicoCenarios.h"
#include "Dominio/Tipos/DisposicaoInicial.h"
#include "Dominio/Tipos/TipoAlgoritmo.h"
#include "Experimentos/ExecutorExperimento.h"

#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <stdexcept>

#include <optional>   // std::optional
#include <iomanip>    // std::fixed e std::setprecision


namespace {

std::size_t lerQuantidade(std::size_t limite) {
    std::size_t quantidade{};

    while (true) {
        std::cout << "\nQuantidade de registros (1 - "
                  << limite << "): ";

        if (std::cin >> quantidade &&
            quantidade > 0 &&
            quantidade <= limite) {
            return quantidade;
        }

        std::cout << "Quantidade inválida. Tente novamente.\n";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


TipoAlgoritmo selecionarAlgoritmo() {
    int opcao{};

    while (true) {
        std::cout << "\nSelecione o algoritmo:\n"
                  << "1 - Selection Sort\n"
                  << "2 - Insertion Sort\n"
                  << "3 - Merge Sort\n"
                  << "4 - Quick Sort\n"
                  << "Opção: ";

        if (std::cin >> opcao) {
            switch (opcao) {
            case 1:
                return TipoAlgoritmo::SelectionSort;
            case 2:
                return TipoAlgoritmo::InsertionSort;
            case 3:
                return TipoAlgoritmo::MergeSort;
            case 4:
                return TipoAlgoritmo::QuickSort;
            }
        }

        std::cout << "Opção inválida. Tente novamente.\n";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


DisposicaoInicial selecionarDisposicao() {
    int opcao{};

    while (true) {
        std::cout << "\nSelecione a disposição inicial:\n"
                  << "1 - Ordenada\n"
                  << "2 - Reversa\n"
                  << "3 - Aleatória\n"
                  << "Opção: ";

        if (std::cin >> opcao) {
            switch (opcao) {
            case 1:
                return DisposicaoInicial::Ordenada;
            case 2:
                return DisposicaoInicial::Reversa;
            case 3:
                return DisposicaoInicial::Aleatoria;
            }
        }

        std::cout << "Opção inválida. Tente novamente.\n";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void apresentarMemoria(
    const char* nome,
    const std::optional<std::uint64_t>& valor
) {
    std::cout << nome << ": ";

    if (valor) {
        const double megabytes =
            static_cast<double>(*valor) / (1024.0 * 1024.0);

        std::cout << std::fixed
                  << std::setprecision(2)
                  << megabytes << " MB\n";
    }
    else {
        std::cout << "Indisponivel\n";
    }
}

};


AplicacaoTerminal::AplicacaoTerminal(
    const std::vector<Registro>& registros)
    : registros_(registros) {
}

void AplicacaoTerminal::executar() {
    apresentarCabecalho();

    // 1. Entrada dos parâmetros.
    const std::size_t quantidade =
        lerQuantidade(registros_.size());

    const TipoAlgoritmo tipoAlgoritmo =
        selecionarAlgoritmo();

    const DisposicaoInicial disposicao =
        selecionarDisposicao();

    // 2. Preparação do cenário selecionado.
    std::random_device dispositivoAleatorio;

    const auto semente = static_cast<std::uint32_t>(dispositivoAleatorio());

    ConjuntoCenarios cenario = ServicoCenarios::gerar(registros_, quantidade, disposicao, semente);

    // 3. Criação do algoritmo selecionado.
    std::unique_ptr<AlgoritmoOrdenacao> algoritmo = CatalogoAlgoritmos::criar(tipoAlgoritmo);


    // Cria o monitor de memória adequado ao sistema operacional.
    std::unique_ptr<MonitorMemoriaProcesso> monitorMemoria = criarMonitorMemoriaProcesso();

    if (!monitorMemoria) {
        throw std::runtime_error(
            "Não foi possível criar o monitor de memória do processo."
        );
    }

    // O ExecutorExperimento recebe o monitor por referência.
    ExecutorExperimento executor(*monitorMemoria);

    // Obtém o vetor do cenário por referência.
    // Não há criação de uma cópia adicional.
    std::vector<Registro>& registrosTrabalho = cenario.obter();

    // Executa o experimento, passando algoritmo e registros por referência.
    ResultadoExecucao resultado = executor.executar(*algoritmo, registrosTrabalho);
    apresentarResultado(resultado);
}

void AplicacaoTerminal::apresentarCabecalho() const {
    std::cout << "\n====================================\n"
              << "        ANALISE DE ORDENACAO\n"
              << "====================================\n"
              << "Dataset disponível: "
              << registros_.size()
              << " registros\n";
}


void AplicacaoTerminal::apresentarResultado(const ResultadoExecucao& resultado) const {

    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "       RESULTADO DO EXPERIMENTO\n";
    std::cout << "========================================\n";

    // Identificação.
    std::cout << "\n[ IDENTIFICACAO ]\n";
    std::cout << "Algoritmo: "
              << resultado.nomeAlgoritmo << '\n';

    // Métricas de ordenação.
    std::cout << "\n[ METRICAS DE ORDENACAO ]\n";

    std::cout << "Tempo: "
              << std::chrono::duration<double, std::milli>(
                     resultado.tempoOrdenacao
                 ).count()
              << " ms\n";

    std::cout << "Comparacoes: "
              << resultado.comparacoes << '\n';

    std::cout << "Movimentacoes: "
              << resultado.movimentacoes << '\n';


    std::cout << "\n[ MEMORIA DO PROCESSO ]\n";

    std::cout << "\nFotografia inicial:\n";

    apresentarMemoria("Working Set", resultado.memoriaInicial.workingSetBytes);

    apresentarMemoria("Uso privado", resultado.memoriaInicial.privateUsageBytes);

    std::cout << "\nFotografia final:\n";

    apresentarMemoria("Working Set", resultado.memoriaFinal.workingSetBytes);

    apresentarMemoria("Uso privado", resultado.memoriaFinal.privateUsageBytes);
}
