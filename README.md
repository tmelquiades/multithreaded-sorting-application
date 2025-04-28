# Sistemas Operacionais I: Projeto - Multithreaded Sorting Application

Uma aplicação em C++ que implementa diversos algoritmos de ordenação e estratégias de paralelização.

## Grupo:
- Gisele Silva Gomes: 20210025824
- Lucas Freire de Lima: 20190115893
- Thaís Melquíades Macedo: 20190021376

## Sobre o Projeto

Esta aplicação foi desenvolvida para demonstrar como algoritmos de ordenação podem ser paralelizados e como diferentes estratégias de paralelização afetam o desempenho. A aplicação inclui:

- Implementação de múltiplos algoritmos de ordenação clássicos
- Diversas estratégias de paralelização 
- Interface de linha de comando
- Visualização dos algoritmos de ordenação
- Benchmark para comparação de desempenho
- Geração de diferentes tipos de dados para testes

## Algoritmos Implementados

### Algoritmos de ordenação usados
- Insertion Sort
- Selection Sort
- Quick Sort
- Merge Sort
- Heap Sort
- Bubble Sort
- Counting Sort
- Radix Sort

### Estratégias de Paralelização
- Divisão de Trabalho: divide o array em segmentos para cada thread
- Quick Sort Paralelo: implementação paralela recursiva do Quick Sort
- Merge Sort Paralelo: implementação paralela recursiva do Merge Sort

## Requisitos

### Para Compilação
- C++17 ou superior
- CMake 3.10 ou superior
- Compilador compatível (GCC, Clang, MSVC)
- Git (para obter dependências)

## Como Compilar

### Compilação Manual

1. Clone o repositório:
   ```bash
   git clone https://github.com/tmelquiades/multithreaded-sorting-application.git
   cd multithreaded-sorting-application
   ```

2. Crie um diretório para build:
   ```bash
   mkdir build
   cd build
   ```

3. Configure e compile o projeto:
   ```bash
   cmake ..
   make -j$(nproc)
   ```

### Usando Docker

É requisito ter o docker instalado.
Para compilar e executar usando Docker:

```bash
docker build -t ordenacao-paralela .
docker run -p 8080:8080 ordenacao-paralela
```

### Usando Imagem Docker - Docker HUB:

É requisito ter o docker instalado.
Para dar um pull na imagem e executar dentro de um shell:
```bash
docker pull giselesilva/ordenacao-paralela:latest
docker run -it giselesilva/ordenacao-paralela:latest /bin/sh
```

## Como Usar

### Interface de Linha de Comando

A aplicação oferece uma interface de linha de comando completa com várias opções:

```bash
./ordenacao_paralela [OPÇÕES]
```

#### Opções Principais:
- `-h, --help`: Mostra a ajuda
- `-m, --modo <modo>`: Define o modo de operação (ordenar, gerar, benchmark)
- `-a, --algoritmo <algoritmo>`: Define o algoritmo de ordenação
- `-e, --estrategia <estrategia>`: Define a estratégia de paralelização
- `-i, --input <arquivo>`: Define o arquivo de entrada
- `-o, --output <arquivo>`: Define o arquivo de saída
- `-s, --tamanho <n>`: Define o tamanho do array para geração
- `-t, --tipo <tipo>`: Define o tipo de dados para geração
- `-p, --threads <n>`: Define o número de threads para paralelização
- `-v, --visualizar`: Habilita visualização básica no terminal
- `-b, --benchmark`: Executa benchmark comparativo

#### Modos disponíveis para usar no CLI:
- `ordenar`: comando para ordenar com base em um arquivo de entrada
- `gerar`: comando para gerar arquivo personalizado
- `benchmark`: comando para executar benchmark personalizado

#### Algoritmos disponíveis para usar no CLI:
- `selection`
- `insertion`
- `quick`
- `merge`
- `heap`
- `bubble`
- `counting`
- `radix`

#### Estratégias disponíveis para usar no CLI:
- `dividir-trabalho`
- `quick-paralelo`
- `merge-paralelo`

#### Tipos de Dados para Teste para usar no CLI:

A aplicação suporta vários tipos de distribuição de dados:

- `aleatorio`: **Aleatório** - Valores distribuídos aleatoriamente
- `ordenado`: **Ordenado** - Valores já em ordem crescente
- `ordenado-inversamente`: **Ordenado Inversamente** - Valores em ordem decrescente
- `parcialmente-ordenado`: **Parcialmente Ordenado** - Maioria dos elementos já ordenados
- `repetido`: **Repetido** - Muitos valores repetidos
- `distribuido`: **Distribuído** - Valores com distribuição normal
  
### Exemplos de Uso:

Ordenar um arquivo usando Quick Sort:
```bash
./ordenacao_paralela -m ordenar -a quick -i dados.txt -o resultado.txt
```

Ordenar paralelamente usando Quick Sort (neste exemplo 8 threads):
```bash
./ordenacao_paralela -m ordenar-paralelo -e quick-paralelo -i dados.txt -o resultado.txt -p 8
```

Gerar dados aleatórios:
```bash
./ordenacao_paralela -m gerar -s 1000000 -t aleatorio -o dados.txt
```

Executar benchmark:
```bash
./ordenacao_paralela -m benchmark --comparar-algoritmos quick,selection,insertion --comparar-estrategias dividir-trabalho,quick-paralelo --tamanhos 10000,100000,1000000 -p 8
```

## Divisão de tarefas entre o grupo:
#### Todos:
- Benchmark
- CLI

#### Gisele Silva:
- implementação heap / counting / radix
- implementação estratégia dividir trabalho
- implementação docker/github actions

#### Lucas Freire:
- implementação bubble / merge
- implementação estratégia merge paralelo
- implementação CMakefile

#### Thaís Melquíades:
- implementação insertion / selection / quick
- implementação estratégia quick paralelo
- implementação gerador de dados
