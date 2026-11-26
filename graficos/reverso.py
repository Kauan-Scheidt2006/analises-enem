from matplotlib.ticker import LogLocator, FuncFormatter
import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

# ==========================================
# DADOS EXPERIMENTAIS - ARRANJO REVERSO (DESORDENADO)
# Tempo em milissegundos (média, desvio padrão)
# ==========================================

quantidades = {
    "10 mil": 10_000,
    "1 milhão": 1_000_000
}

dados = {
    "Selection Sort": {
        10_000: (455.430, 2.450),
        100_000: (38200.0, 350.0),
        500_000: (940000.0, 5000.0),
        1_000_000: None, 
        4_810_740: None
    },
    "Insertion Sort": {
        10_000: (713.340, 20.300),
        100_000: (64200.0, 500.0),
        500_000: (1580000.0, 8000.0),
        1_000_000: None, 
        4_810_740: None
    },
    "Quick Sort": {
        10_000: (1.895, 0.215),
        100_000: (14.200, 0.200),
        500_000: (78.500, 1.100),
        1_000_000: (175.360, 2.370),
        4_810_740: (986.020, 38.640)
    },
    "Merge Sort": {
        10_000: (2.274, 0.344),
        100_000: (16.800, 0.250),
        500_000: (89.100, 1.300),
        1_000_000: (189.340, 4.600),
        4_810_740: (1122.680, 12.390)
    }
}

cores_algoritmos = {
    "Selection Sort": {"medido": "#2980b9", "curva": "#e67e22"},
    "Insertion Sort": {"medido": "#27ae60", "curva": "#c0392b"},
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

    # Selection e Insertion: projeção quadrática O(n²)
    if algoritmo in ["Selection Sort", "Insertion Sort"]:
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
    # Quick e Merge: ajuste empírico
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
    "Tempo de Ordenação — Vetor Reverso (Pior Caso)",
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
    "grafico_reverso.png",
    dpi=300,
    bbox_inches="tight"
)

plt.show()
