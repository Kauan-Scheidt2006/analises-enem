#include <QCoreApplication>
#include <QFile>
#include <QStringList>

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <vector>

#include "Leitura/LeitorCSV.h"
#include "Terminal/AplicacaoTerminal.h"

namespace {

std::filesystem::path converterCaminho(const QString& caminho) {
#ifdef Q_OS_WIN
    return std::filesystem::path(caminho.toStdWString());
#else
    const QByteArray caminhoLocal = QFile::encodeName(caminho);
    return std::filesystem::path(caminhoLocal.constData());
#endif
}

} // namespace

int main(int argc, char* argv[]) {
    QCoreApplication aplicacao(argc, argv);

    const QStringList argumentos = aplicacao.arguments();

    const std::filesystem::path caminhoDataset =
        argumentos.size() > 1
            ? converterCaminho(argumentos.at(1))
            : converterCaminho(QCoreApplication::applicationDirPath()) /
                  "dataset" / "banco.csv";

    try {
        LeitorCSV leitor;

        const std::vector<Registro> registros =
            leitor.carregar(caminhoDataset);

        std::cout << "Dataset carregado com sucesso: "
                  << registros.size()
                  << " registros.\n";

        AplicacaoTerminal terminal(registros);

        terminal.executar();

        return EXIT_SUCCESS;

    } catch (const std::exception& erro) {
        std::cerr << "\nErro: " << erro.what() << '\n';
        return EXIT_FAILURE;
    }
}