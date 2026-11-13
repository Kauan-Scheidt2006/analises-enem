# Trabalho 2: Análise de Algoritmos de Ordenação

**Disciplina:** Estrutura de Dados  
**Professor:** Lucas Dominguez Cordeiro  
**Curso:** Engenharia de Computação — IFC Campus São Bento do Sul  
**Equipe:** Vitor Nogueira e Kauan

---

# 🏛️ Estrutura das Classes Principais

## 1. `Registro` — Modelo de Dados

**Responsabilidade:** Representar cada registro do dataset e definir a chave utilizada na ordenação.

**Atributos principais:**
- `num_inscricao` (`int64_t`): chave principal de ordenação.
- Demais campos relevantes do dataset, caso sejam necessários para preservar os dados originais.

**Métodos necessários:**
- Sobrecarga dos operadores de comparação (`<`, `>`, `<=`, `>=`, `==`), utilizando exclusivamente a chave `num_inscricao`.
- Construtores para inicialização dos registros.

## 2. `LeitorCSV` — Parser de Dados

**Responsabilidade:** Realizar a leitura do dataset e transformar seus registros em um vetor de objetos `Registro`.

**Métodos necessários:**
- `lerArquivo(string caminho)`: abre o arquivo CSV e carrega os registros em um `std::vector<Registro>`.
- Identificação das colunas utilizadas no dataset.
- Conversão dos valores para os tipos adequados.
- Tratamento de exceções para arquivos inexistentes, inválidos ou mal-formatados.

**Observação:** A leitura do dataset deve acontecer antes dos benchmarks, não sendo contabilizada no tempo de execução dos algoritmos.

## 3. `GeradorCenarios` — Gerenciador de Cenários e Embaralhamento

**Responsabilidade:** Criar os diferentes padrões de entrada utilizados nos experimentos.

**Métodos necessários:**
- `gerarCopia(const std::vector<Registro>& original)`: retorna uma cópia independente do vetor original.
- `gerarOrdenado(const std::vector<Registro>& original)`: prepara o cenário de dados ordenados.
- `gerarReverso(const std::vector<Registro>& original)`: inverte o vetor ordenado, criando o cenário decrescente.
- `embaralhar(std::vector<Registro>& vetor, unsigned int seed)`: embaralha o vetor utilizando uma semente fixa para garantir reprodutibilidade.
- `gerarAmostra(const std::vector<Registro>& original, size_t quantidade)`: gera as amostras de 10 mil, 100 mil e 1 milhão de registros.

**Observação:** Caso o dataset não esteja originalmente ordenado, será necessário preparar o vetor ordenado antes de gerar os demais cenários.

## 4. `AlgoritmoBase` — Interface de Ordenação

**Responsabilidade:** Padronizar a implementação e a coleta de métricas dos algoritmos.

**Atributos protegidos:**
- `num_comparacoes` (`uint64_t`): contador de comparações entre elementos.
- `num_movimentacoes` (`uint64_t`): contador de movimentações de elementos.

**Métodos públicos/abstratos:**
- `ordenar(std::vector<Registro>& vetor)`: método virtual responsável pela execução da ordenação.
- `getComparacoes()`: retorna o número de comparações.
- `getMovimentacoes()`: retorna o número de movimentações.
- `resetContadores()`: zera os contadores antes de cada execução.

**Observação:** Todos os algoritmos devem seguir a mesma interface. A definição do que será contabilizado como movimentação deve ser padronizada e documentada.

## 5. `Medidor` — Módulo de Benchmark

**Responsabilidade:** Coordenar os experimentos, medir o desempenho e armazenar os resultados.

**Métodos necessários:**
- Executar determinado algoritmo sobre uma cópia independente do vetor de entrada.
- Medir o tempo de execução utilizando `std::chrono`.
- Coletar o número de comparações por meio de `getComparacoes()`.
- Coletar o número de movimentações por meio de `getMovimentacoes()`.
- Registrar o tamanho do vetor, o algoritmo e o cenário utilizado.
- Realizar múltiplas repetições dos experimentos.
- Calcular média e desvio-padrão dos tempos.
- Exportar os resultados para arquivos CSV.

**Observação:** O tempo medido deve considerar exclusivamente a ordenação, excluindo leitura, cópia, geração de cenários e validação.

---

# 📅 Roteiro Cronológico de Desenvolvimento e Divisão de Tarefas

## Fase 1: Infraestrutura de Dados, Parser e Geração de Cenários

> **Objetivo:** Preparar o dataset, implementar a leitura dos registros e criar os três padrões de entrada nas três variações de tamanho (10k, 100k e 1M).

### Passos

**1. [Vitor] Preparação do dataset**

- Preparar e organizar o dataset no repositório.
- Verificar a integridade dos dados.
- Identificar a coluna que será utilizada como chave de ordenação.
- Verificar se o dataset possui pelo menos 1 milhão de registros.
- Garantir que os dados possam ser utilizados nos três cenários.

**2. [Kauan] Implementação da classe `Registro`**

- Criar os atributos necessários.
- Implementar os construtores.
- Sobrecargar os operadores de comparação utilizando `num_inscricao`.
- Garantir que as comparações sejam realizadas exclusivamente pela chave de ordenação.

**3. [Vitor] Implementação da classe `LeitorCSV`**

- Implementar a abertura e leitura do arquivo CSV.
- Identificar e acessar as colunas necessárias.
- Converter os valores para os tipos adequados.
- Armazenar os registros em `std::vector<Registro>`.
- Implementar tratamento de erros para arquivos inexistentes ou mal-formatados.

**4. [Kauan] Implementação da classe `GeradorCenarios`**

- Implementar a geração de cópias independentes dos vetores.
- Implementar a geração do cenário ordenado.
- Implementar a geração do cenário em ordem reversa.
- Implementar o embaralhamento utilizando uma seed fixa.
- Implementar a geração das amostras de 10k, 100k e 1M registros.

**5. [Vitor e Kauan] Integração e validação na `main.cpp`**

- Carregar o dataset utilizando `LeitorCSV`.
- Gerar as três amostras.
- Aplicar as três transformações em cada amostra.
- Imprimir algumas posições dos vetores para verificar os resultados.
- Confirmar que os cenários foram gerados corretamente.
- Verificar se as cópias são independentes e não alteram o vetor original.

**Resultado esperado:** Infraestrutura de dados funcionando e pronta para receber os algoritmos.

---

## Fase 2: Interface Base e Implementação dos Algoritmos

> **Objetivo:** Definir a estrutura comum dos algoritmos e implementar os quatro métodos de ordenação exigidos, incluindo a contagem de comparações e movimentações.

### Passos

**1. [Kauan] Implementação da classe `AlgoritmoBase`**

- Criar os atributos protegidos:
  - `num_comparacoes`.
  - `num_movimentacoes`.
- Definir o método virtual `ordenar()`.
- Implementar `getComparacoes()`.
- Implementar `getMovimentacoes()`.
- Implementar `resetContadores()`.
- Garantir que todos os algoritmos utilizem a mesma interface.

**2. [Vitor] Implementação do `SelectionSort`**

- Implementar a lógica de seleção do menor elemento.
- Incrementar `num_comparacoes` a cada comparação entre dois registros.
- Incrementar `num_movimentacoes` a cada atribuição ou troca de registros, conforme a convenção definida.
- Reiniciar os contadores antes de cada execução.
- Garantir que o vetor seja ordenado corretamente.

**3. [Kauan] Implementação do `InsertionSort`**

- Implementar a lógica de inserção dos elementos em suas posições corretas.
- Incrementar `num_comparacoes` a cada comparação entre registros.
- Incrementar `num_movimentacoes` a cada deslocamento de elemento.
- Contabilizar a atribuição do elemento armazenado temporariamente na posição correta.
- Reiniciar os contadores antes de cada execução.
- Garantir que o vetor seja ordenado corretamente.

**4. [Vitor] Implementação do `QuickSort`**

- Implementar a lógica de particionamento do vetor.
- Definir e documentar a estratégia de escolha do pivô.
- Incrementar `num_comparacoes` nas comparações realizadas durante o particionamento.
- Incrementar `num_movimentacoes` nas trocas de elementos.
- Garantir que as chamadas recursivas respeitem os limites do vetor.
- Considerar estratégias para evitar profundidade excessiva de recursão.
- Reiniciar os contadores antes de cada execução.

**5. [Kauan] Pesquisa e implementação do segundo algoritmo eficiente (`MergeSort` ou `HeapSort`)**

- Pesquisar o funcionamento e a complexidade do algoritmo.
- Justificar a escolha no artigo técnico.
- Implementar a lógica de ordenação.
- Incrementar `num_comparacoes` nas comparações entre registros.
- Incrementar `num_movimentacoes` nas cópias, deslocamentos ou trocas de elementos, conforme a estratégia utilizada.
- Considerar o uso de memória auxiliar, caso necessário.
- Reiniciar os contadores antes de cada execução.

**6. [Vitor e Kauan] Integração e validação dos algoritmos**

- Garantir que os quatro algoritmos utilizem a interface `AlgoritmoBase`.
- Verificar se os contadores estão funcionando corretamente.
- Comparar os resultados com `std::sort`, exclusivamente para validação.
- Testar com vetores pequenos, ordenados, reversos e aleatórios.
- Verificar se todos os algoritmos produzem resultados corretos.

**Resultado esperado:** Quatro algoritmos implementados, testados e padronizados.

---

## Fase 3: Módulo de Benchmark, Execução dos Testes e Validação

> **Objetivo:** Desenvolver o módulo de medição e executar os experimentos utilizando os três padrões de entrada e os três tamanhos de amostra.

### Passos

**1. [Vitor] Implementação da função de validação**

- Verificar se o vetor está realmente ordenado após cada execução.
- Comparar o resultado com uma referência confiável.
- Garantir que a validação aconteça fora do intervalo cronometrado.
- Confirmar que o algoritmo não perdeu ou duplicou registros durante a ordenação.

**2. [Kauan] Implementação da classe `Medidor`**

- Implementar a medição de tempo utilizando `std::chrono`.
- Registrar o instante inicial imediatamente antes da chamada de `ordenar()`.
- Registrar o instante final imediatamente após o término da ordenação.
- Calcular a duração em milissegundos.
- Coletar o número de comparações utilizando `getComparacoes()`.
- Coletar o número de movimentações utilizando `getMovimentacoes()`.
- Registrar o tamanho do vetor utilizando `vetor.size()`.
- Registrar o nome do algoritmo e o cenário utilizado.
- Reiniciar os contadores antes de cada execução.
- Organizar os resultados das repetições.
- Calcular a média e o desvio-padrão dos tempos.

**Exemplo da temporização dentro do `Medidor`:**

```cpp
auto inicio = std::chrono::high_resolution_clock::now();

algoritmo.ordenar(vetor);

auto fim = std::chrono::high_resolution_clock::now();

double tempo = std::chrono::duration<double, std::milli>(
    fim - inicio
).count();
```

**Métricas que deverão ser coletadas:**

| Métrica | Forma de obtenção |
|---|---|
| Tempo de execução | `std::chrono` |
| Comparações | `getComparacoes()` |
| Movimentações | `getMovimentacoes()` |
| Tamanho do vetor | `vetor.size()` |
| Algoritmo | Identificação do algoritmo |
| Cenário | Ordenado, reverso ou aleatório |
| Repetição | Número da execução |

**3. [Vitor e Kauan] Integração do módulo de benchmark**

Organizar e executar a bateria de testes.

**Cenário 1 — Dados ordenados:**
- 10.000 registros.
- 100.000 registros.
- 1.000.000 de registros.

**Cenário 2 — Dados em ordem reversa:**
- 10.000 registros.
- 100.000 registros.
- 1.000.000 de registros.

**Cenário 3 — Dados aleatórios:**
- 10.000 registros.
- 100.000 registros.
- 1.000.000 de registros.

**Critérios de execução:**

- Utilizar a mesma entrada para todos os algoritmos em cada experimento.
- Criar uma cópia independente do vetor antes de cada execução.
- Fixar a seed do cenário aleatório.
- Realizar, preferencialmente, no mínimo cinco repetições.
- Aplicar warm-up quando pertinente.
- Medir exclusivamente o tempo de ordenação.
- Reiniciar os contadores antes de cada execução.
- Validar a saída após cada execução.
- Estabelecer um limite de tempo para os algoritmos quadráticos nos tamanhos maiores.
- Registrar os experimentos interrompidos e suas justificativas.

**Resultado esperado:** Bateria de testes funcionando e resultados confiáveis para análise.

---

## Fase 4: Coleta de Dados, Gráficos e Artigo Técnico

> **Objetivo:** Organizar os resultados dos experimentos, produzir gráficos e desenvolver o artigo técnico com base nos dados coletados.

### Passos

**1. [Vitor] Exportação dos resultados**

- Organizar os dados coletados pelo `Medidor`.
- Gerar arquivos CSV com os resultados.
- Separar os resultados por algoritmo, tamanho e cenário.
- Garantir que os arquivos contenham todas as métricas necessárias.
- Preservar os resultados individuais das repetições para permitir análises posteriores.

**2. [Kauan] Geração dos gráficos comparativos**

- Gerar gráficos de tempo de execução × tamanho do dataset.
- Gerar gráficos de comparações × tamanho do dataset.
- Gerar gráficos de movimentações × tamanho do dataset.
- Comparar o desempenho dos algoritmos nos diferentes cenários.
- Utilizar escala logarítmica quando apropriado.
- Identificar eixos, unidades e legendas.

**3. [Vitor e Kauan] Desenvolvimento do artigo técnico**

Produzir o artigo técnico com 4 a 6 páginas, seguindo o formato SBC ou IEEE.

**Estrutura do artigo:**

- Introdução.
- Fundamentação teórica.
- Metodologia.
- Resultados.
- Discussão.
- Conclusão.
- Referências.

**Pontos que devem ser abordados:**

- Complexidade Big-O dos algoritmos no melhor, médio e pior caso.
- Justificativa da escolha do dataset e da chave de ordenação.
- Descrição do ambiente de testes.
- Comparação entre os resultados teóricos e práticos.
- Análise dos gráficos e das métricas.
- Discussão sobre os limites dos algoritmos quadráticos.
- Justificativa dos experimentos não executados, quando houver.
- Declaração do uso de ferramentas de inteligência artificial, quando aplicável.

**Resultado esperado:** Artigo técnico completo, fundamentado nos resultados efetivamente obtidos.

---

# ⚠️ Pontos Críticos de Integração

Para evitar incompatibilidades e resultados incorretos, algumas regras devem ser seguidas durante o desenvolvimento.

## 1. Alteração dos vetores durante a ordenação

**Problema:** Os algoritmos recebem o vetor por referência (`std::vector<Registro>&`) e modificam seus elementos durante a execução. Se o mesmo vetor for reutilizado, os próximos testes poderão receber dados já ordenados.

**Solução:** Criar uma cópia independente do cenário original antes de cada execução. Nenhum algoritmo deve modificar os vetores-base utilizados para gerar os experimentos.

## 2. Reprodutibilidade dos dados aleatórios

**Problema:** Se cada algoritmo receber um vetor aleatório diferente, a comparação de desempenho não será justa.

**Solução:** Utilizar uma seed fixa para gerar o cenário aleatório. Todos os algoritmos devem receber cópias dos mesmos dados de entrada.

## 3. Inclusão de operações externas na medição

**Problema:** Medir o tempo de leitura do CSV, criação de cópias, embaralhamento ou validação junto com a ordenação.



**Solução:** Preparar o vetor antes de iniciar o cronômetro. Medir exclusivamente a execução do algoritmo.

## 4. Estouro de memória ou pilha no QuickSort

**Problema:** Uma escolha inadequada de pivô pode produzir partições muito desbalanceadas, aumentando a profundidade da recursão.

**Solução:** Considerar estratégias como mediana de três e recursão apenas na menor partição, processando a maior iterativamente. Documentar a estratégia utilizada.

## 5. Diferenças na contagem de movimentações

**Problema:** Cada algoritmo realiza operações diferentes para movimentar os elementos. Sem uma regra comum, os resultados podem ser inconsistentes.

**Solução:** Definir uma convenção de contagem antes da implementação.

Como referência:
- Uma atribuição de um registro conta como uma movimentação.
- Uma troca utilizando variável temporária representa três movimentações.
- Um deslocamento de elemento representa uma movimentação.
- No MergeSort, as cópias para o vetor auxiliar também devem ser contabilizadas.

A convenção deve ser aplicada de maneira consistente em todos os algoritmos.

## 6. Limites dos algoritmos quadráticos

**Problema:** Selection Sort e Insertion Sort podem apresentar tempos muito elevados com grandes quantidades de registros.

**Solução:** Estabelecer um limite máximo de tempo por execução. Registrar até qual tamanho cada algoritmo foi efetivamente executado e justificar eventuais interrupções no artigo.

## 7. Consistência dos experimentos

**Problema:** Executar os algoritmos em condições diferentes pode comprometer a comparação.

**Solução:**
- Utilizar a mesma máquina.
- Manter os mesmos dados de entrada.
- Utilizar as mesmas condições de execução.
- Realizar múltiplas repetições.
- Registrar o ambiente de hardware e software.
- Não apresentar estimativas como se fossem medições reais.

---

# 📁 Organização Sugerida do Repositório

```text
Trabalho02-Ordenacao/
│
├── dados/
│   └── dataset.csv
│
├── src/
│   ├── modelos/
│   │   ├── Registro.h
│   │   └── Registro.cpp
│   │
│   ├── leitura/
│   │   ├── LeitorCSV.h
│   │   └── LeitorCSV.cpp
│   │
│   ├── cenarios/
│   │   ├── GeradorCenarios.h
│   │   └── GeradorCenarios.cpp
│   │
│   ├── algoritmos/
│   │   ├── AlgoritmoBase.h
│   │   ├── SelectionSort.h
│   │   ├── InsertionSort.h
│   │   ├── QuickSort.h
│   │   └── MergeSort.h
│   │
│   ├── benchmark/
│   │   ├── Medidor.h
│   │   └── Medidor.cpp
│   │
│   └── main.cpp
│
├── resultados/
│   ├── csv/
│   └── graficos/
│
├── artigo/
│   └── artigo.pdf
│
├── apresentacao/
│   └── slides.pdf
│
├── README.md
└── .gitignore
```

---
## 📁 Dataset

Para executar o projeto corretamente, é necessário baixar o dataset utilizado nas análises.

<details>
<summary><strong>📥 Baixar dataset (Google Drive)</strong></summary>

[**Clique aqui para baixar o dataset**](https://drive.google.com/file/d/1oe6d0PZKo26wYISa9OE20MlNmVmp7FIi/view?usp=drive_link)

</details>

Após o download, coloque o arquivo na pasta `dataset` do projeto, mantendo a seguinte estrutura:

    analises-enem/
    ├── dataset/
    │   └── banco.csv

**Importante:** mantenha o nome do arquivo como `banco.csv` para que o programa consiga localizá-lo corretamente.
# ✅ Checklist de Entrega

### Implementação

- [x] Dataset público com pelo menos 10.000 registros.
- [x] Chave de ordenação definida e justificada.
- [x] Classe `Registro` implementada.
- [x] Classe `LeitorCSV` implementada.
- [x] Serviço de cenários implementado.
- [x] Classe `AlgoritmoBase` implementada.
- [x] Selection Sort implementado.
- [ ] Insertion Sort implementado.
- [ ] QuickSort implementado.
- [ ] Segundo algoritmo eficiente implementado.
- [x] Contadores de comparações implementados(selection).
- [x] Contadores de movimentações implementados(selection).

### Benchmarks

- [ ] Três padrões de entrada implementados.
- [ ] Três tamanhos de amostra preparados.
- [ ] Temporização com `std::chrono` implementada.
- [ ] Coleta de todas as métricas implementada.
- [ ] Repetições e análise estatística realizadas.
- [ ] Correção dos resultados validada.
- [ ] Limites dos algoritmos quadráticos documentados.
- [ ] Resultados exportados para CSV.

### Documentação e entrega

- [ ] Gráficos comparativos gerados.
- [ ] Ambiente de testes documentado.
- [ ] Artigo técnico (4 a 6 páginas) finalizado.
- [ ] Slides da apresentação finalizados.
- [ ] README com instruções de compilação e execução.
- [ ] Declaração de uso de IA incluída no artigo, quando aplicável.
- [ ] Participação dos integrantes registrada no histórico de commits.
- [ ] Repositório preparado para entrega no SIGAA.
- [ ] Versão final registrada por tag ou release.

---

**Observação final:** A divisão de tarefas representa a responsabilidade principal de cada integrante. As etapas de integração, validação e escrita do artigo devem ser realizadas em conjunto para garantir que ambos compreendam a implementação e os resultados apresentados.

---

# Compilação e execução com Qt

O projeto utiliza C++20, Qt 6.5 ou superior, CMake e Ninja. Os presets mantêm builds independentes para Windows e Linux.

## Windows

O ambiente Windows configurado utiliza Qt 6.11.1 e o MinGW fornecido pela instalação do Qt.

```bat
configurar.bat debug
compilar.bat debug
executar.bat debug
```

Para compilar em Release ou informar outro CSV:

```bat
compilar.bat release
executar.bat release "C:\caminho\para\arquivo.csv"
```

Os executáveis são gerados em `build/windows-debug/bin` e `build/windows-release/bin`.

## Linux

Instale um compilador C++20, CMake, Ninja e os arquivos de desenvolvimento do Qt 6 Core. Quando o Qt não estiver instalado nos caminhos do sistema, defina `QT_ROOT` para a raiz do kit:

```sh
export QT_ROOT="$HOME/Qt/6.11.1/gcc_64"
```

Garanta a permissão de execução dos scripts e execute:

```sh
chmod +x configurar.sh compilar.sh executar.sh
./configurar.sh debug
./compilar.sh debug
./executar.sh debug
```

Para compilar em Release ou informar outro CSV:

```sh
./compilar.sh release
./executar.sh release "/caminho/para/arquivo.csv"
```

Os executáveis são gerados em `build/linux-debug/bin` e `build/linux-release/bin`.
