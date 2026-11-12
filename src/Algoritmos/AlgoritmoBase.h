#pragma once
#include <vector>
#include <chrono>
using namespace std;

class AlgoritmoBase{
    protected:
    long long num_comparacoes{0};
    long long num_movimentacoes{0};
    chrono::microseconds tempoExecucao{0};
};
