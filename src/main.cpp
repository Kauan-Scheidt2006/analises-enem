#include <QCoreApplication>
#include <QFile>
#include <QStringList>

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <vector>

#include "Cenarios/ServicoCenarios.h"
#include "Leitura/LeitorCSV.h"
#include "Algoritmos/SelectionSort.h"

namespace {

std::filesystem::path converterCaminho(const QString& caminho) {
#ifdef Q_OS_WIN
    return std::filesystem::path(caminho.toStdWString());
#else
    const QByteArray caminhoLocal = QFile::encodeName(caminho);
    return std::filesystem::path(caminhoLocal.constData());
#endif
}

}  // namespace

int main(int argc, char* argv[]) {
    SelectionSort ordenador;
    QCoreApplication aplicacao(argc, argv);

    const QStringList argumentos = aplicacao.arguments();
    const std::filesystem::path caminhoDataset = argumentos.size() > 1
        ? converterCaminho(argumentos.at(1))
        : converterCaminho(QCoreApplication::applicationDirPath()) /
              "dataset" / "banco.csv";

    try {
        LeitorCSV leitor;
        const std::vector<Registro> registros = leitor.carregar(caminhoDataset);
        std::cout << "Dataset carregado: " << registros.size() << " registros\n";

        ServicoCenarios::configurar({});
        const ColecaoCenarios cenarios =
            ServicoCenarios::gerarTodos(registros);

        for (const ConjuntoCenarios& conjunto : cenarios) {
            std::cout << "Amostra: " << conjunto.tamanho << " registros\n";
            ordenador.selectionSort(conjunto.obter(TipoCenario::Ordenado));
        }

        return EXIT_SUCCESS;
    } catch (const std::exception& erro) {
        std::cerr << "Erro: " << erro.what() << '\n';
        return EXIT_FAILURE;
    }
}
