#include "Cenarios/ConjuntoCenarios.h"

std::vector<Registro>& ConjuntoCenarios::obter() noexcept {
    return registros;
}

const std::vector<Registro>& ConjuntoCenarios::obter() const noexcept {
    return registros;
}