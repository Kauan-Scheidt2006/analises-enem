#!/usr/bin/env bash
set -euo pipefail

raiz="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
configuracao="${1:-debug}"

case "$configuracao" in
    debug|release) ;;
    *)
        echo "ERRO: Configuração inválida: $configuracao" >&2
        echo "Uso: ./configurar.sh [debug|release]" >&2
        exit 2
        ;;
esac

for ferramenta in cmake ninja g++; do
    if ! command -v "$ferramenta" >/dev/null 2>&1; then
        echo "ERRO: Ferramenta não encontrada no PATH: $ferramenta" >&2
        exit 1
    fi
done

if [[ -n "${QT_ROOT:-}" && ! -f "$QT_ROOT/lib/cmake/Qt6/Qt6Config.cmake" ]]; then
    echo "ERRO: QT_ROOT não aponta para um kit Qt 6 válido: $QT_ROOT" >&2
    exit 1
fi

cd "$raiz"
cmake --preset "linux-$configuracao"
