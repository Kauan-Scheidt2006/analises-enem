#include "AlgoritmoBase.h"
#include "../Registro/Registro.h"
#include <vector>

class SelectionSort : public AlgoritmoBase{
    long long num_comparacoes{0};
    long long num_movimentacoes{0};
    chrono::microseconds tempoExecucao{0};
    public:
    vector<Registro> selectionSort(vector<Registro> registro);
};
