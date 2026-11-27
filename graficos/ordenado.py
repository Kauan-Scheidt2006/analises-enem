from matplotlib.ticker import LogLocator, FuncFormatter
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

# ==========================================
# DADOS EXPERIMENTAIS - ARRANJO ORDENADO
# Tempo em milissegundos (média, desvio padrão)
# ==========================================

quantidades = {
    "10 mil": 10_000,
    "1 milhão": 1_000_000
}

dados = {
    "Selection Sort": {
        10_000: (287.126, 4.420),
        100_000: (25100.0, 300.0),
        500_000: (612000.0, 4000.0),
        1_000_000: (3278100.0, 15000.0), 
        4_810_740: None
    },
    "Insertion Sort": {
        10_000: (0.0838, 0.0299),
        100_000: (0.650, 0.050),
        500_000: (3.250, 0.120),
        1_000_000: (6.500, 0.052), 
        4_810_740: (31.801, 0.310)
    },
    "Quick Sort": {
        10_000: (1.320, 0.058),
        100_000: (12.800, 0.150),
        500_000: (71.200, 1.200),
        1_000_000: (170.850, 6.640),
        4_810_740: (1120.740, 196.480)
    },
    "Merge Sort": {
        10_000: (1.605, 0.190),
        100_000: (14.500, 0.200),
        500_000: (80.500, 1.000),
        1_000_000: (186.760, 9.870),
        4_810_740: (1071.980, 71.950)
    }
}

cores_algoritmos = {
    "Selection Sort": {"medido": "#2980b9", "curva": "#e67e22"},
    "Insertion Sort": {"medido": "#27ae60", "curva": "#27ae60"},
    "Quick Sort":     {"medido": "#8e44ad", "curva": "#8d6e63"},
    "Merge Sort":     {"medido": "#e84393", "curva": "#7f8c8d"}
}

# ==========================================
# FUNÇÕES DE PROJEÇÃO E AJUSTE EMPÍRICO
# ==========================================

def projetar_quadratico(n, n_base, tempo_base):
    """
    Projeção baseada em O(n²).
    """
    return tempo_base * (n / n_base) ** 2

def ajustar_potencia(pontos_n, pontos_t):
    """
    Ajusta T(n) = a * n^b
    utilizando regressão linear em escala log-log.
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

    # Selection Sort: projeção quadrática O(n²)
    if algoritmo == "Selection Sort":
        tempo_base = resultados[10_000][0]
        y = projetar_quadratico(
            x,
            10_000,
            tempo_base
        )
        ax.plot(
            x,
            y,
            linestyle='--',
            linewidth=2,
            color=cores_algoritmos[algoritmo]["curva"],
            label=f"{algoritmo} - projeção O(n²)"
        )
    # Insertion, Quick e Merge: ajuste empírico
    else:
        pontos_validos = [
            (n, resultado[0])
            for n, resultado in resultados.items()
            if resultado is not None
        ]

        n_medidos = np.array([
            ponto[0] for ponto in pontos_validos
        ])
        tempos_medidos = np.array([
            ponto[1] for ponto in pontos_validos
        ])

        a, b = ajustar_potencia(
            n_medidos,
            tempos_medidos
        )

        y = projetar_potencia(x, a, b)
        ax.plot(
            x,
            y,
            linewidth=2,
            color=cores_algoritmos[algoritmo]["curva"],
            label=f"{algoritmo} - ajuste empírico (n^{b:.2f})"
        )

# ==========================================
# FORMATAÇÃO
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
    "Tempo de Ordenação — Vetor Ordenado (Melhor Caso)",
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
    "grafico_ordenado.png",
    dpi=300,
    bbox_inches="tight"
)

plt.show()
