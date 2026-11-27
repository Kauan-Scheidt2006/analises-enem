from matplotlib.ticker import LogLocator, FuncFormatter
import numpy as np
import matplotlib.pyplot as plt

# ==========================================
# DADOS EXPERIMENTAIS - CASO MÉDIO (MOVIMENTAÇÕES)
# ==========================================

dados = {
    "Selection Sort": {
        10_000: 29_970,
        100_000: 299_973,
        500_000: 1_499_952,
        1_000_000: None,
        4_810_720: None
    },
    "Insertion Sort": {
        10_000: 24_931_177,
        100_000: 2_500_318_695,
        500_000: 62_509_651_533,
        1_000_000: None,
        4_810_720: None
    },
    "Quick Sort": {
        10_000: 105_504,
        100_000: 1_297_254,
        500_000: 7_228_415,
        1_000_000: 15_175_743,
        4_810_720: 81_102_742
    },
    "Merge Sort": {
        10_000: 140_000,
        100_000: 1_800_000,
        500_000: 10_000_000,
        1_000_000: 20_000_000,
        4_810_720: 115_458_528
    }
}

cores_algoritmos = {
    "Selection Sort": {"medido": "#2980b9", "curva": "#e67e22"},
    "Insertion Sort": {"medido": "#27ae60", "curva": "#c0392b"},
    "Quick Sort":     {"medido": "#8e44ad", "curva": "#8d6e63"},
    "Merge Sort":     {"medido": "#e84393", "curva": "#7f8c8d"}
}

def projetar_linear(n, n_base, val_base):
    return val_base * (n / n_base)

def projetar_quadratico(n, n_base, val_base):
    return val_base * (n / n_base) ** 2

def ajustar_potencia(pontos_n, pontos_y):
    expoente, log_coeficiente = np.polyfit(np.log(pontos_n), np.log(pontos_y), 1)
    return np.exp(log_coeficiente), expoente

def projetar_potencia(n, coeficiente, expoente):
    return coeficiente * n ** expoente

# ==========================================
# CONFIGURAÇÃO DO GRÁFICO
# ==========================================

x = np.logspace(4, np.log10(4_810_720), 500)
fig, ax = plt.subplots(figsize=(12, 8))

# ==========================================
# CONSTRUÇÃO DAS CURVAS
# ==========================================

for algoritmo, resultados in dados.items():
    px = [q for q, r in resultados.items() if r is not None]
    py = [r for q, r in resultados.items() if r is not None]

    ax.plot(
        px, py, 'o', markersize=7,
        color=cores_algoritmos[algoritmo]["medido"],
        label=f"{algoritmo} - medido"
    )

    if algoritmo == "Selection Sort":
        val_base = resultados[10_000]
        y = projetar_linear(x, 10_000, val_base)
        ax.plot(
            x, y, '--', linewidth=2,
            color=cores_algoritmos[algoritmo]["curva"],
            label=f"{algoritmo} - projeção O(n)"
        )
    elif algoritmo == "Insertion Sort":
        val_base = resultados[10_000]
        y = projetar_quadratico(x, 10_000, val_base)
        ax.plot(
            x, y, '--', linewidth=2,
            color=cores_algoritmos[algoritmo]["curva"],
            label=f"{algoritmo} - projeção O(n²)"
        )
    else:
        a, b = ajustar_potencia(np.array(px), np.array(py))
        y = projetar_potencia(x, a, b)
        ax.plot(
            x, y, '-', linewidth=2,
            color=cores_algoritmos[algoritmo]["curva"],
            label=f"{algoritmo} - ajuste empírico (n^{b:.2f})"
        )

# ==========================================
# FORMATAÇÃO DOS EIXOS
# ==========================================

ax.set_xscale("log")
ax.set_yscale("log")

ax.xaxis.set_major_locator(LogLocator(base=10, subs=(1.0, 2.0, 5.0)))
ax.xaxis.set_major_formatter(FuncFormatter(lambda val, _: f"{val:,.0f}".replace(",", ".")))
ax.yaxis.set_major_formatter(FuncFormatter(lambda val, _: f"{val:,.0f}".replace(",", ".")))
ax.xaxis.set_minor_locator(LogLocator(base=10, subs=(3.0, 4.0, 6.0, 7.0, 8.0, 9.0)))

ax.set_xlabel("Quantidade de registros (n)", fontsize=15, labelpad=10)
ax.set_ylabel("Movimentações na RAM (M)", fontsize=15, labelpad=10)
ax.set_title("Volume de movimentações na RAM em função da quantidade de registros", fontsize=17, pad=15)

ax.grid(True, which="both", linestyle=":", alpha=0.6)
ax.legend(fontsize=11, loc="best", framealpha=0.9)
ax.set_xlim(8_000, 6_000_000)

ax.tick_params(axis="both", which="major", labelsize=12)
ax.tick_params(axis="both", which="minor", labelsize=10)

plt.tight_layout()
plt.savefig("grafico_movimentacoes_aleatorio.png", dpi=300, bbox_inches="tight")
plt.show()
