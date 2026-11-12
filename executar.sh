#!/usr/bin/env bash
set -euo pipefail

raiz="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
configuracao="${1:-debug}"
caminho_csv="${2:-}"

case "$configuracao" in
    debug|release) ;;
    *)
        echo "ERRO: Configuração inválida: $configuracao" >&2
        echo "Uso: ./executar.sh [debug|release] [caminho-csv]" >&2
        exit 2
        ;;
esac

executavel="$raiz/build/linux-$configuracao/bin/analises_enem"

if [[ ! -x "$executavel" ]]; then
    echo "ERRO: Executável não encontrado: $executavel" >&2
    echo "Execute ./compilar.sh $configuracao primeiro." >&2
    exit 1
fi

if [[ -n "${QT_ROOT:-}" ]]; then
    export LD_LIBRARY_PATH="$QT_ROOT/lib:${LD_LIBRARY_PATH:-}"
fi

if [[ -n "$caminho_csv" ]]; then
    exec "$executavel" "$caminho_csv"
else
    exec "$executavel"
fi
