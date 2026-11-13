#include "SelectionSort.h"
#include <cstddef>
#include <chrono>
#include <utility>
#include <vector>
#include <iostream>
using namespace std;

vector<Registro> SelectionSort::selectionSort(vector<Registro> registros) {
    auto inicio = chrono::steady_clock::now();

    long long comparacoes = 0;
    long long movimentacoes = 0;
    size_t tamanho = registros.size();

    for (size_t i = 0; i < tamanho - 1; i++) {
        comparacoes++;
        size_t menor = i;

        for (size_t j = i + 1; j < tamanho; j++) {
            comparacoes++;

            comparacoes++;
            if (registros[j].inscricao < registros[menor].inscricao) {
                menor = j;
            }

        }
        comparacoes++;
        if (menor != i) {
            swap(registros[i], registros[menor]);
            movimentacoes++;
        }
    }
    comparacoes++; //

    this->num_comparacoes = comparacoes;
    this-> num_movimentacoes = movimentacoes;
    auto fim = chrono::steady_clock::now();
    this->tempoExecucao = chrono::duration_cast<chrono::microseconds>(fim - inicio);
    cout<<"vetor ordenado no selection sort\n"<<endl;
    cout<<"tempo de execucao: "<<this->tempoExecucao.count()<<"\n"<<endl;
    cout<<"numero de comparacoes: "<<this->num_comparacoes<<"\n"<<endl;
    cout<<"numero de movimentacoes: "<<this->num_movimentacoes<<"\n"<<endl;
    return registros;
}
