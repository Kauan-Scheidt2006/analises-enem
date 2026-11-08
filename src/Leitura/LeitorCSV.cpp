#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "LeitorCSV.h"

vector<Registro> LeitorCSV::carregarCSV(const string caminhoDataset){
  vector<Registro> registros;
  ifstream arquivo(caminhoDataset);

  if (!arquivo.is_open()) {
      cout<<"erro ao abrir data set: "<<caminhoDataset<<endl;
      return registros;
  }

string linha;
getline(arquivo,linha);

    while (getline(arquivo,linha)) {
       Registro reg;
       reg.inscricao = stoll(linha);

       registros.push_back(reg);
    };
arquivo.close();
return registros;
};
