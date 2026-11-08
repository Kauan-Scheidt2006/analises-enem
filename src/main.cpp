#include <iostream>
#include <vector>
#include <string>
#include "Leitura/LeitorCSV.h"

using namespace std;

int main(){
    string caminhoDataset = "dataset/banco.csv";

    vector<Registro> registros = LeitorCSV::carregarCSV(caminhoDataset);

    cout << "Registros carregados: " << registros.size() << "\n";
    return 0;
}
