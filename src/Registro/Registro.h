#pragma once

#include <cstdint>

struct Registro {
    std::uint64_t inscricao{};

    Registro() = default;
    explicit Registro(std::uint64_t numeroInscricao) noexcept
        : inscricao(numeroInscricao) {}

    [[nodiscard]] bool operator<(const Registro& outro) const noexcept {
        return inscricao < outro.inscricao;
    }

    [[nodiscard]] bool operator>(const Registro& outro) const noexcept {
        return inscricao > outro.inscricao;
    }

    [[nodiscard]] bool operator<=(const Registro& outro) const noexcept {
        return inscricao <= outro.inscricao;
    }

    [[nodiscard]] bool operator>=(const Registro& outro) const noexcept {
        return inscricao >= outro.inscricao;
    }

    [[nodiscard]] bool operator==(const Registro& outro) const noexcept {
        return inscricao == outro.inscricao;
    }
};
