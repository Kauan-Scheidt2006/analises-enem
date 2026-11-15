
#include "ValidadorResultado.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

bool ValidadorResultado::validar(
    const std::vector<Registro>& resultado,
    const std::vector<Registro>& registrosOriginais,
    std::size_t quantidade
) {
    std::cout << "\n========== DIAGNOSTICO DA VALIDACAO ==========\n";

    // 1. Verificar quantidade solicitada.
    std::cout << "\n[1] Quantidade solicitada: "
              << quantidade << '\n';

    std::cout << "[1] Registros originais: "
              << registrosOriginais.size() << '\n';

    std::cout << "[1] Registros do resultado: "
              << resultado.size() << '\n';

    if (quantidade > registrosOriginais.size()) {
        std::cout << "ERRO: quantidade maior que os registros originais.\n";
        return false;
    }

    if (resultado.size() != quantidade) {
        std::cout << "ERRO: tamanho do resultado diferente da quantidade solicitada.\n";
        return false;
    }

    // 2. Construir a referência.
    std::vector<Registro> referencia(
        registrosOriginais.begin(),
        std::next(
            registrosOriginais.begin(),
            static_cast<std::vector<Registro>::difference_type>(quantidade)
        )
    );

    std::cout << "\n[2] Referencia criada com sucesso.\n";

    // 3. Verificar se a referência está ordenada.
    std::sort(referencia.begin(), referencia.end());

    std::cout << "[3] Referencia ordenada com std::sort.\n";

    // 4. Verificar se o resultado está ordenado.
    const bool resultadoOrdenado = std::is_sorted(
        resultado.begin(),
        resultado.end()
    );

    std::cout << "\n[4] Resultado esta ordenado? "
              << (resultadoOrdenado ? "SIM" : "NAO") << '\n';

    if (!resultadoOrdenado) {
        std::cout << "ERRO: o vetor produzido pelo algoritmo nao esta ordenado.\n";

        for (std::size_t i = 1; i < resultado.size(); ++i) {
            if (resultado[i] < resultado[i - 1]) {
                std::cout << "Primeira inversao encontrada na posicao "
                          << i << '\n';

                std::cout << "Anterior: "
                          << resultado[i - 1].inscricao << '\n';

                std::cout << "Atual: "
                          << resultado[i].inscricao << '\n';

                break;
            }
        }

        return false;
    }

    // 5. Comparar os vetores.
    std::cout << "\n[5] Comparando resultado com referencia...\n";

    if (resultado == referencia) {
        std::cout << "VALIDACAO APROVADA.\n";
        return true;
    }

    std::cout << "ERRO: os vetores possuem conteudos diferentes.\n";

    // 6. Localizar a primeira divergência.
    for (std::size_t i = 0; i < resultado.size(); ++i) {
        if (resultado[i] != referencia[i]) {
            std::cout << "\nPrimeira divergencia na posicao: "
                      << i << '\n';

            std::cout << "Resultado: "
                      << resultado[i].inscricao << '\n';

            std::cout << "Referencia: "
                      << referencia[i].inscricao << '\n';

            break;
        }
    }

    std::cout << "\n========== FIM DO DIAGNOSTICO ==========\n";

    return false;
}
