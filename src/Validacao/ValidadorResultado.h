#include "../Registro/Registro.h"

#include <vector>


class ValidadorResultado final {
public:
    [[nodiscard]] static bool validar(const std::vector<Registro>& resultado, const std::vector<Registro>& registrosOriginais, std::size_t quantidade);
};
