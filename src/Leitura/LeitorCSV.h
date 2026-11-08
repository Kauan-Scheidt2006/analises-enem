#include "../Registro/Registro.h"
using namespace std;
#include <vector>
#include <string>

class LeitorCSV{
    public:
    static vector<Registro> carregarCSV(const string caminhoDataset);
};
