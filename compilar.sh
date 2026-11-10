#!/usr/bin/env bash
set -euo pipefail

raiz="$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)"
configuracao="${1:-debug}"

"$raiz/configurar.sh" "$configuracao"

cd "$raiz"
cmake --build --preset "linux-$configuracao"
