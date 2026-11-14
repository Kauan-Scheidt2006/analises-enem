#pragma once

#include <chrono>

class MedidorTempo {
public:
    class Escopo {
    public:
        explicit Escopo(
            std::chrono::nanoseconds& duracao
        ) noexcept
            : duracao_(duracao),
              inicio_(Relogio::now()) {
        }

        ~Escopo() noexcept {
            const auto fim = Relogio::now();

            duracao_ =
                std::chrono::duration_cast<std::chrono::nanoseconds>(
                    fim - inicio_
                );
        }

        Escopo(const Escopo&) = delete;
        Escopo& operator=(const Escopo&) = delete;

        Escopo(Escopo&&) = delete;
        Escopo& operator=(Escopo&&) = delete;

    private:
        using Relogio = std::chrono::steady_clock;

        std::chrono::nanoseconds& duracao_;
        Relogio::time_point inicio_;
    };
};

