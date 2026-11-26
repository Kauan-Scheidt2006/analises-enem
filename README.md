# 📊 Análise Experimental de Algoritmos de Ordenação sobre Dados do ENEM

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg?logo=c%2B%2B)
![Qt](https://img.shields.io/badge/Qt-6.5%2B-green.svg?logo=qt)
![CMake](https://img.shields.io/badge/CMake-Build-orange.svg?logo=cmake)
![Status](https://img.shields.io/badge/Status-Acad%C3%AAmico-lightgrey.svg)

Projeto desenvolvido em **C++20** para analisar e comparar o desempenho de diferentes algoritmos de ordenação utilizando os microdados do **ENEM 2025**.

O trabalho avalia o comportamento dos algoritmos em diferentes volumes e padrões de dados, considerando tempo de execução, número de comparações, movimentações e consumo de memória.

---

## ⚙️ Algoritmos Implementados

Foram implementados e analisados quatro algoritmos:

* **Selection Sort**
* **Insertion Sort**
* **Merge Sort:** versão iterativa (*bottom-up*).
* **Quick Sort:** implementação híbrida.

> A ordenação utiliza a coluna `NU_INSCRICAO` como chave. Essa coluna possui valores únicos e ordenados, permitindo utilizar as inscrições como referência para a comparação dos algoritmos.

---

## 📂 Dataset

O dataset utilizado corresponde aos microdados do **ENEM 2025** e já está incluído junto ao código do projeto (`dados/dataset.csv`). O conjunto completo possui **4.810.720 registros**.

**Tamanhos de entrada avaliados:**
* `10.000` registros
* `100.000` registros
* `500.000` registros
* `1.000.000` registros
* `4.810.720` registros (conjunto completo)

**Padrões de entrada testados:**
* **Ordenado**
* **Inversamente ordenado**
* **Aleatório**

Para garantir a consistência dos experimentos, cada algoritmo recebe uma cópia independente do vetor original. A validação dos resultados é realizada por comparação com a ordenação da biblioteca padrão (`std::sort`).

---

## 📏 Métricas Analisadas

O desempenho dos algoritmos foi avaliado considerando:

* **Tempo de execução:** medido com `std::chrono::high_resolution_clock`.
* **Comparações:** quantidade de comparações realizadas entre as chaves.
* **Movimentações:** quantidade de atribuições, trocas e cópias de elementos.
* **Consumo de memória:** *Working Set* e *Private Bytes*.

Cada cenário foi executado **cinco vezes**, utilizando a média e o desvio padrão dos resultados. Foi estabelecido um limite máximo de **50 minutos** por execução.

---

## 📈 Resultados Experimentais

A tabela abaixo apresenta os resultados médios do cenário com **entradas aleatórias**, considerando cinco execuções independentes:

| Registros | Algoritmo | Tempo médio | Comparações | Movimentações |
| :--- | :--- | :---: | :---: | :---: |
| **10.000** | Selection Sort | 348,5 ms | 49.995.000 | 29.970 |
| **10.000** | Insertion Sort | 261,4 ms | 24.931.175 | 24.931.177 |
| **10.000** | Quick Sort | 3,24 ms | 196.678 | 105.504 |
| **10.000** | Merge Sort | 3,53 ms | 123.658 | 140.000 |
| **100.000** | Selection Sort | 29,8 s | 4.999.950.000 | 299.973 |
| **100.000** | Insertion Sort | 23,4 s | 2.500.318.698 | 2.500.318.695 |
| **100.000** | Quick Sort | 25,5 ms | 2.393.650 | 1.297.254 |
| **100.000** | Merge Sort | 28,8 ms | 1.567.512 | 1.800.000 |
| **500.000** | Selection Sort | 13,1 min | 124.999.750.000 | 1.499.952 |
| **500.000** | Insertion Sort | 9,5 min | 62.509.651.534 | 62.509.651.533 |
| **500.000** | Quick Sort | 142,9 ms | 13.512.940 | 7.228.415 |
| **500.000** | Merge Sort | 162,9 ms | 8.857.619 | 10.000.000 |
| **1.000.000** | Selection Sort | *Interrompido* | — | — |
| **1.000.000** | Insertion Sort | *Interrompido* | — | — |
| **1.000.000** | Quick Sort | 668,1 ms | 28.236.720 | 15.175.743 |
| **1.000.000** | Merge Sort | 776,2 ms | 18.716.376 | 20.000.000 |
| **4.810.720** | Selection Sort | *Não executado* | — | — |
| **4.810.720** | Insertion Sort | *Não executado* | — | — |
| **4.810.720** | Quick Sort | 1,98 s | 147.204.942 | 81.102.742 |
| **4.810.720** | Merge Sort | 1,94 s | 103.117.766 | 115.458.528 |

**Observações:**
* **Selection Sort** e **Insertion Sort** ultrapassaram o limite de execução estabelecido no teste com 1 milhão de registros.
* Os resultados desses dois algoritmos para `4.810.720` registros não foram medidos; o artigo apresenta apenas estimativas teóricas.
* No conjunto completo, **Merge Sort** apresentou o menor tempo médio, enquanto **Quick Sort** realizou menos movimentações.

---

## 💻 Ambiente de Execução

**Ambiente principal dos experimentos:**
* **Sistema operacional:** Windows 11 64 bits
* **Processador:** AMD Ryzen 7 5825U
* **Memória RAM:** 32 GB DDR4
* **Compilador:** GCC com otimização `-O2`

**Ambiente secundário de validação:**
* **Sistema operacional:** Arch Linux
* **Processador:** AMD Ryzen 7 7454HS
* **Memória RAM:** 16 GB

---

## 🛠️ Tecnologias Utilizadas

* **C++20**
* **Qt 6.5** ou superior
* **CMake**
* **Ninja**
* **GCC / MinGW**

> **Nota:** O programa é executado pelo terminal, sem interface gráfica. A dependência do Qt faz parte da configuração do projeto.

---

## 📁 Estrutura do Projeto

    Trabalho02-Ordenacao/
    ├── dados/
    │   └── dataset.csv
    ├── src/
    │   ├── modelos/
    │   ├── leitura/
    │   ├── cenarios/
    │   ├── algoritmos/
    │   └── benchmark/
    ├── resultados/
    │   ├── csv/
    │   └── graficos/
    ├── artigo/
    │   └── artigo.pdf
    ├── apresentacao/
    │   └── slides.pdf
    ├── README.md
    └── .gitignore

---

## 🚀 Compilação e Execução

### 🪟 Windows

O projeto utiliza o Qt com MinGW. Com as dependências instaladas e configuradas:

**Modo Debug:**

    configurar.bat debug
    compilar.bat debug
    executar.bat debug

**Modo Release:**

    compilar.bat release
    executar.bat release "C:\caminho\para\arquivo.csv"

Os executáveis são gerados em:
* `build/windows-debug/bin/`
* `build/windows-release/bin/`

### 🐧 Linux

Instale um compilador compatível com C++20, CMake, Ninja e os arquivos de desenvolvimento do **Qt 6 Core**.

Caso o Qt esteja instalado em um diretório personalizado, configure a variável de ambiente:

    export QT_ROOT="$HOME/Qt/6.11.1/gcc_64"

Dê permissão de execução aos scripts:

    chmod +x configurar.sh compilar.sh executar.sh

**Modo Debug:**

    ./configurar.sh debug
    ./compilar.sh debug
    ./executar.sh debug

**Modo Release:**

    ./compilar.sh release
    ./executar.sh release "/caminho/para/arquivo.csv"

Os executáveis são gerados em:
* `build/linux-debug/bin/`
* `build/linux-release/bin/`

---

## 📄 Documentação

O artigo técnico apresenta a metodologia experimental, os resultados obtidos, as análises comparativas e as conclusões do trabalho:

* [`artigo/artigo.pdf`](artigo/artigo.pdf) — artigo técnico completo.
* [`apresentacao/slides.pdf`](apresentacao/slides.pdf) — apresentação do trabalho.

---

## ✒️ Autores

* **Vitor N. Souza**
* **Kauan F. Scheidt**

**Instituto Federal Catarinense — Campus São Bento do Sul (IFC SBS)**

---

*Projeto acadêmico desenvolvido para análise experimental e comparação de algoritmos de ordenação.*

