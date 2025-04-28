// cli.cpp
#include "cli.h"
#include "algoritmos_ordenacao/algoritmos_ordenacao.h"
#include "ordenacao_paralela.h"
#include "gerador_dados.h"
#include "benchmark.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <thread>
#include <chrono>
#include <fstream>

namespace cli {

void imprimirAjuda() { // a parte do help (-h)
    std::cout << "Uso: ordenacao_paralela [OPCOES]\n\n";
    std::cout << "Aplicação de ordenação paralela em C++.\n\n";
    std::cout << "Opções:\n";
    std::cout << "  -h, --help                      Mostra esta ajuda\n";
    std::cout << "  -m, --modo <modo>               Define o modo de operação (ordenar, gerar, benchmark)\n";
    std::cout << "  -a, --algoritmo <algoritmo>     Define o algoritmo de ordenação a ser usado\n";
    std::cout << "  -e, --estrategia <estrategia>   Define a estratégia de paralelização\n";
    std::cout << "  -i, --input <arquivo>           Define o arquivo de entrada\n";
    std::cout << "  -o, --output <arquivo>          Define o arquivo de saída\n";
    std::cout << "  -s, --tamanho <n>               Define o tamanho do array para geração\n";
    std::cout << "  -t, --tipo <tipo>               Define o tipo de dados para geração\n";
    std::cout << "  -p, --threads <n>               Define o número de threads para paralelização\n";
    std::cout << "  -v, --visualizar                Habilita visualização (apenas para CLI)\n";
    std::cout << "  -b, --benchmark                 Executa benchmark comparativo\n";
    std::cout << "  --comparar-algoritmos <alg1,alg2,...> Algoritmos a comparar no benchmark\n";
    std::cout << "  --comparar-estrategias <est1,est2,...> Estratégias a comparar no benchmark\n";
    std::cout << "  --tamanhos <t1,t2,...>          Tamanhos a testar no benchmark\n";
    std::cout << "  --repeticoes <n>                Número de repetições para cada teste\n";
    std::cout << "\n";
    
    // Imprimindo tabelinha de ajuda com os argumentos:
    // Obter os dados
    auto algoritmos = ordenacao::obterNomesAlgoritmos();
    auto estrategias = ordenacao_paralela::obterNomesEstrategias();
    auto tipos = gerador::obterNomesTipos();
    
    // Determinar o número máximo de itens em qualquer lista
    size_t maxItens = std::max({algoritmos.size(), estrategias.size(), tipos.size()});
    
    // Determinar a largura máxima para cada coluna
    size_t larguraAlgoritmos = 0;
    size_t larguraEstrategias = 0;
    size_t larguraTipos = 0;
    
    for (const auto& alg : algoritmos) {
        larguraAlgoritmos = std::max(larguraAlgoritmos, alg.length());
    }
    for (const auto& est : estrategias) {
        larguraEstrategias = std::max(larguraEstrategias, est.length());
    }
    for (const auto& tipo : tipos) {
        larguraTipos = std::max(larguraTipos, tipo.length());
    }
    
    // Adicionar espaço para padding
    larguraAlgoritmos += 5;
    larguraEstrategias += 4;
    larguraTipos += 3;
    
    // Imprimir cabeçalhos
    std::cout << std::setw(larguraAlgoritmos) << std::left << "Algoritmos" 
              << std::setw(larguraEstrategias) << std::left << "Estratégias" 
              << std::setw(larguraTipos) << std::left << " Tipos de Dados" << std::endl;
    
    // Imprimir linha de separação
    std::cout << std::string(larguraAlgoritmos-2, '-') << " "
              << std::string(larguraEstrategias, '-') << " "
              << std::string(larguraTipos-3, '-') << std::endl;
    
    // Imprimir itens lado a lado
    for (size_t i = 0; i < maxItens; i++) {
        // Imprimir algoritmo se disponível
        if (i < algoritmos.size()) {
            std::cout << std::setw(larguraAlgoritmos) << std::left << algoritmos[i];
        } else {
            std::cout << std::setw(larguraAlgoritmos) << "";
        }
        
        // Imprimir estratégia se disponível
        if (i < estrategias.size()) {
            std::cout << std::setw(larguraEstrategias) << std::left << estrategias[i];
        } else {
            std::cout << std::setw(larguraEstrategias) << "";
        }
        
        // Imprimir tipo de dados se disponível
        if (i < tipos.size()) {
            std::cout << std::setw(larguraTipos) << std::left << tipos[i];
        } else {
            std::cout << std::setw(larguraTipos) << "";
        }
        
        std::cout << std::endl;
    }
}

void executarComandos(const Opcoes& opcoes) {
    if (opcoes.modo == "ordenar" || opcoes.modo == "ordenar-paralelo") {
        executarOrdenacaoSimples(opcoes);
    } else if (opcoes.modo == "gerar") {
        executarGeracaoDados(opcoes);
    } else if (opcoes.modo == "benchmark") {
        executarBenchmark(opcoes);
    } else {
        std::cerr << "Modo desconhecido: " << opcoes.modo << "\n";
        std::cerr << "Use --help para obter ajuda.\n";
    }
}

// auxiliar para dividir string em vetor
std::vector<std::string> dividirString(const std::string& s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;
    
    while (getline(ss, item, delim)) {
        if (!item.empty()) {
            result.push_back(item);
        }
    }
    
    return result;
}

// auxiliar para dividir string em vetor de inteiros
std::vector<int> dividirStringInteiros(const std::string& s, char delim) {
    std::vector<int> result;
    std::stringstream ss(s);
    std::string item;
    
    while (getline(ss, item, delim)) {
        if (!item.empty()) {
            try {
                result.push_back(std::stoi(item));
            } catch (const std::invalid_argument&) {
                // Ignorar valores não numéricos
            }
        }
    }
    
    return result;
}

// pega os argumentos que o usuario escreveu e guarda em opcoes
Opcoes parseArgumentos(int argc, char* argv[]) {
    Opcoes opcoes;
    
    // valores padrão para as opcoes
    opcoes.modo = "ordenar";
    opcoes.algoritmo = "quick";
    opcoes.estrategia = "dividir-trabalho";
    opcoes.tamanho = 10000;
    opcoes.tipoDados = "aleatorio";
    opcoes.numThreads = std::thread::hardware_concurrency();
    opcoes.visualizar = false;
    opcoes.benchmark = false;
    opcoes.repeticoes = 3;
    
    // padrões para benchmark
    opcoes.algoritmosComparar = {"quick", "merge", "heap"};
    opcoes.estrategiasComparar = {"dividir-trabalho", "merge-paralelo", "quick-paralelo"};
    opcoes.tamanhos = {10000, 100000, 1000000};
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        
        if (arg == "-h" || arg == "--help") {
            imprimirAjuda();
            exit(0);
        } else if (arg == "-m" || arg == "--modo") {
            if (i + 1 < argc) opcoes.modo = argv[++i];
        } else if (arg == "-a" || arg == "--algoritmo") {
            if (i + 1 < argc) opcoes.algoritmo = argv[++i];
        } else if (arg == "-e" || arg == "--estrategia") {
            if (i + 1 < argc) opcoes.estrategia = argv[++i];
        } else if (arg == "-i" || arg == "--input") {
            if (i + 1 < argc) opcoes.arquivoEntrada = argv[++i];
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) opcoes.arquivoSaida = argv[++i];
        } else if (arg == "-s" || arg == "--tamanho") {
            if (i + 1 < argc) opcoes.tamanho = std::stoi(argv[++i]);
        } else if (arg == "-t" || arg == "--tipo") {
            if (i + 1 < argc) opcoes.tipoDados = argv[++i];
        } else if (arg == "-p" || arg == "--threads") {
            if (i + 1 < argc) opcoes.numThreads = std::stoi(argv[++i]);
        } else if (arg == "-v" || arg == "--visualizar") {
            opcoes.visualizar = true;
        } else if (arg == "-b" || arg == "--benchmark") {
            opcoes.benchmark = true;
        } else if (arg == "--comparar-algoritmos") {
            if (i + 1 < argc) opcoes.algoritmosComparar = dividirString(argv[++i], ','); // varios argumentos, ent divide
        } else if (arg == "--comparar-estrategias") {
            if (i + 1 < argc) opcoes.estrategiasComparar = dividirString(argv[++i], ',');
        } else if (arg == "--tamanhos") {
            if (i + 1 < argc) opcoes.tamanhos = dividirStringInteiros(argv[++i], ','); // varios int, divide
        } else if (arg == "--repeticoes") {
            if (i + 1 < argc) opcoes.repeticoes = std::stoi(argv[++i]); // numero de repeticoes
        }
    }
    
    return opcoes;
}

// Função auxiliar para visualizar o estado do array durante a ordenação
void visualizarArray(const std::vector<int>& arr, int max_mostrar = 30) {
    // Limpar terminal (funciona em sistemas Unix/Linux)
    std::cout << "\033[2J\033[1;1H";
    
    int tamanho = arr.size();
    int mostrar = std::min(tamanho, max_mostrar);
    
    // Encontrar valor máximo para escala
    int max_val = *std::max_element(arr.begin(), arr.end());
    int escala = 50;  // Tamanho máximo de barra
    
    for (int i = 0; i < mostrar; i++) {
        int idx = i * tamanho / mostrar;
        int val = arr[idx];
        int tamanho_barra = static_cast<int>(val * escala / max_val);
        
        std::cout << std::setw(8) << val << " |";
        for (int j = 0; j < tamanho_barra; j++) {
            std::cout << "#";
        }
        std::cout << "\n";
    }
    
    std::cout << "Array size: " << tamanho << "\n";
    std::cout.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}

// executar ordenação simples
void executarOrdenacaoSimples(const Opcoes& opcoes) {
    // carregar dados
    std::vector<int> dados;
    
    if (!opcoes.arquivoEntrada.empty()) { // se usuario não passa arquivo de entrada ele gera dados aleatorios
        try {
            dados = gerador::lerArquivo(opcoes.arquivoEntrada);
            std::cout << "Dados carregados do arquivo: " << opcoes.arquivoEntrada << "\n";
        } catch (const std::exception& e) {
            std::cerr << "Erro ao ler arquivo: " << e.what() << "\n";
            return;
        }
    } else {
        // gerar dados aleatórios
        auto tipo = gerador::obterTipoPorNome(opcoes.tipoDados);
        dados = gerador::gerarDados(opcoes.tamanho, tipo);
        std::cout << "Dados gerados: " << opcoes.tamanho << " elementos, tipo: " << opcoes.tipoDados << "\n";
    }
    
    // mostrar dados antes da ordenação (limitado)
    if (opcoes.visualizar) { // se o usuario escolher visualizar como ele vai ordenando
        std::cout << "Dados originais:\n";
        visualizarArray(dados);
    }
    
    // obter algoritmo e estratégia
    auto algoritmo = ordenacao::obterAlgoritmo(opcoes.algoritmo);
    
    // medir tempo
    auto inicio = std::chrono::high_resolution_clock::now();
    
    // executar algoritmo (sequencial ou paralelo)
    if (opcoes.modo == "ordenar-paralelo") {
        if (ordenacao_paralela::ehEstrategiaEspecifica(opcoes.estrategia)) {
            auto estrategia = ordenacao_paralela::obterEstrategiaEspecifica(opcoes.estrategia);
            estrategia(dados, opcoes.numThreads);
        } else {
            auto estrategia = ordenacao_paralela::obterEstrategia(opcoes.estrategia);
            estrategia(dados, algoritmo, opcoes.numThreads);
        }
        std::cout << "Ordenação paralela executada: " << opcoes.algoritmo << " + " << opcoes.estrategia << "\n";
    } else {
        algoritmo(dados);
        std::cout << "Ordenação sequencial executada: " << opcoes.algoritmo << "\n";
    }
    
    auto fim = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duracao = fim - inicio;
    
    // mostrar dados após ordenação (limitado)
    if (opcoes.visualizar) {
        std::cout << "Dados ordenados:\n";
        visualizarArray(dados);
    }
    
    // verificar se está ordenado
    bool ordenado = benchmark::verificarOrdenacao(dados); // para ordenacao correta
    
    std::cout << "Tempo de execução: " << duracao.count() << " ms\n";
    std::cout << "Ordenação correta: " << (ordenado ? "Sim" : "Não") << "\n";
    
    // salvar resultado
    if (!opcoes.arquivoSaida.empty()) { // se usuario não passa arquivo de saida ele não guarda em nenhum lugar, só ordena
        bool salvo = gerador::salvarArquivo(dados, opcoes.arquivoSaida);
        if (salvo) {
            std::cout << "Dados salvos em: " << opcoes.arquivoSaida << "\n";
        } else {
            std::cerr << "Erro ao salvar arquivo: " << opcoes.arquivoSaida << "\n";
        }
    }
}

// executar geração de dados
void executarGeracaoDados(const Opcoes& opcoes) {
    if (opcoes.arquivoSaida.empty()) {
        std::cerr << "Erro: É necessário especificar um arquivo de saída para geração de dados.\n";
        return;
    }
    
    auto tipo = gerador::obterTipoPorNome(opcoes.tipoDados); // pega o tipo pelo nome do tipo
    auto dados = gerador::gerarDados(opcoes.tamanho, tipo); // pega o gerar dados la do gerador e passa o tamanho e o tipo
    
    bool salvo = gerador::salvarArquivo(dados, opcoes.arquivoSaida); // salva o resultado no arquivo de saída
    if (salvo) { // mostra que salvou
        std::cout << "Dados gerados salvos em: " << opcoes.arquivoSaida << "\n";
        std::cout << "Tamanho: " << opcoes.tamanho << " elementos\n";
        std::cout << "Tipo: " << opcoes.tipoDados << "\n";
    } else {
        std::cerr << "Erro ao salvar arquivo: " << opcoes.arquivoSaida << "\n";
    }
}

// executar benchmark
void executarBenchmark(const Opcoes& opcoes) {
    std::cout << "Iniciando benchmark...\n";
    
    // dados aleatórios para o benchmark
    bool dadosAleatorios = true;
    
    // executar benchmarks
    auto resultados = benchmark::executarBenchmarks(
        opcoes.algoritmosComparar, 
        opcoes.estrategiasComparar, 
        opcoes.tamanhos, 
        opcoes.numThreads, 
        opcoes.repeticoes, 
        dadosAleatorios
    );
    
    // Exibir resultados
    std::cout << "\nResultados do benchmark:\n";
    
    std::cout << std::left << std::setw(60) << "Algoritmo/Estratégia" 
              << std::right << std::setw(15) << "Tempo (ms)" 
              << std::setw(15) << "Ordenado?" << "\n";
    std::cout << std::string(90, '-') << "\n";
    
    for (const auto& resultado : resultados) {
        std::cout << std::left << std::setw(60) << resultado.nome 
                  << std::right << std::setw(15) << std::fixed << std::setprecision(2) << resultado.tempo 
                  << std::setw(15) << (resultado.correto ? "Sim" : "Não") << "\n";
    }

    std::cout << "==========================================================================================" << std::endl;
    
    // Salvar resultados em arquivo se especificado
    if (!opcoes.arquivoSaida.empty()) {
        std::ofstream arquivo(opcoes.arquivoSaida);
        if (arquivo.is_open()) {
            arquivo << "Algoritmo/Estratégia,Tempo (ms),Ordenado\n";
            
            for (const auto& resultado : resultados) {
                arquivo << resultado.nome << "," 
                        << std::fixed << std::setprecision(2) << resultado.tempo << "," 
                        << (resultado.correto ? "Sim" : "Não") << "\n";
            }
            
            arquivo.close();
            std::cout << "\nResultados salvos em: " << opcoes.arquivoSaida << "\n";
        } else {
            std::cerr << "Erro ao salvar resultados em arquivo: " << opcoes.arquivoSaida << "\n";
        }
    }
}

} // namespace cli