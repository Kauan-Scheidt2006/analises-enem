from matplotlib.ticker import LogLocator, FuncFormatter
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

# ==========================================
# DADOS EXPERIMENTAIS - ARRANJO ALEATÓRIO (CASO MÉDIO)
# Tempo em milissegundos (média, desvio padrão)
# ==========================================

dados = {
    "Selection Sort": {
        10_000: (347.845, 8.085),
        100_000: (29890.98, 249.79),
        500_000: (786316.860, 4806.143),
        1_000_000: None, 
        4_810_740: None
    },
    "Insertion Sort": {
        10_000: (257.720, 11.030),
        100_000: (23513.40, 225.71),
        500_000: (572905.300, 1281.286),
        1_000_000: None, 
        4_810_740: None
    },
    "Quick Sort": {
        10_000: (3.422, 0.435),
        100_000: (25.52824, 0.15320),
        500_000: (142.897, 1.538),
        1_000_000: (668.158, 19.221),
        4_810_740: (1989.258, 911.791)
    },
    "Merge Sort": {
        10_000: (4.136, 0.909),
        100_000: (28.77294, 0.20426),
        500_000: (162.947, 0.903),
        1_000_000: (776.368, 37.743),
        4_810_740: (1938.784, 20.043)
    }
}

cores_algoritmos = {
    "Selection Sort": {"medido": "#2980b9", "curva": "#e67e22"},
    "Insertion Sort": {"medido": "#27ae60", "curva": "#c0392b"},
    "Quick Sort":     {"medido": "#8e44ad", "curva": "#8d6e63"},
    "Merge Sort":     {"medido": "#e84393", "curva": "#7f8c8d"}
}

# ==========================================
# FUNÇÕES DE AJUSTE EMPÍRICO
# ==========================================

def ajustar_potencia(pontos_n, pontos_t):
    """
    Ajusta T(n) = a * n^b utilizando regressão linear em escala log-log.
    """
    expoente, log_coeficiente = np.polyfit(
        np.log(pontos_n),
        np.log(pontos_t),
        1
    )
    coeficiente = np.exp(log_coeficiente)
    return coeficiente, expoente

def projetar_potencia(n, coeficiente, expoente):
    return coeficiente * n ** expoente

# ==========================================
# CONFIGURAÇÃO DO GRÁFICO
# ==========================================

x = np.logspace(4, np.log10(4_810_740), 500)
fig, ax = plt.subplots(figsize=(12, 8))

# ==========================================
# CONSTRUÇÃO DAS CURVAS
# ==========================================

for algoritmo, resultados in dados.items():
    pontos_x = []
    pontos_y = []
    desvios = []

    for quantidade, resultado in resultados.items():
        if resultado is not None:
            tempo, desvio = resultado
            pontos_x.append(quantidade)
            pontos_y.append(tempo)
            desvios.append(desvio)

    # Pontos efetivamente medidos
    ax.errorbar(
        pontos_x,
        pontos_y,
        yerr=desvios,
        fmt='o',
        capsize=4,
        markersize=7,
        color=cores_algoritmos[algoritmo]["medido"],
        label=f"{algoritmo} - medido"
    )

    # Ajuste empírico para TODOS os algoritmos
    a, b = ajustar_potencia(np.array(pontos_x), np.array(pontos_y))
    y = projetar_potencia(x, a, b)

    # Linha tracejada para os métodos quadráticos (sinalizando extrapolação além de 500k)
    ls = '--' if algoritmo in ["Selection Sort", "Insertion Sort"] else '-'

    ax.plot(
        x,
        y,
        linestyle=ls,
        linewidth=2,
        color=cores_algoritmos[algoritmo]["curva"],
        label=f"{algoritmo} - ajuste empírico (n^{b:.2f})"
    )

# ==========================================
# FORMATAÇÃO DO GRÁFICO
# ==========================================

ax.set_xscale("log")
ax.set_yscale("log")

# Marcações principais e intermediárias do eixo X
ax.xaxis.set_major_locator(
    LogLocator(base=10, subs=(1.0, 2.0, 5.0))
)

# Formatação dos valores em milhares e milhões
ax.xaxis.set_major_formatter(
    FuncFormatter(lambda x, _: f"{x:,.0f}".replace(",", "."))
)

ax.xaxis.set_minor_locator(
    LogLocator(base=10, subs=(3.0, 4.0, 6.0, 7.0, 8.0, 9.0))
)

ax.set_xlabel(
    "Quantidade de registros (n)",
    fontsize=15,
    labelpad=10
)

ax.set_ylabel(
    "Tempo de ordenação (ms)",
    fontsize=15,
    labelpad=10
)

ax.set_title(
    "Tempo de Ordenação — Vetor Aleatório (Caso Médio)",
    fontsize=17,
    pad=15
)

ax.grid(
    True,
    which="both",
    linestyle=":",
    alpha=0.6
)

ax.legend(
    fontsize=11,
    loc="best",
    framealpha=0.9
)

ax.set_xlim(8_000, 6_000_000)

ax.tick_params(
    axis="both",
    which="major",
    labelsize=12
)

ax.tick_params(
    axis="both",
    which="minor",
    labelsize=10
)

plt.tight_layout()

plt.savefig(
    "grafico_aleatorio.png",
    dpi=300,
    bbox_inches="tight"
)
