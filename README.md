# LinquesProblem

## Trabalho Prático de Estruturas de Dados - Escapando da Floresta da Neblina
Descrição do Projeto
Este projeto foi desenvolvido como parte do curso de Estrutura de Dados da Universidade Federal de Minas Gerais (UFMG). O objetivo principal do trabalho é implementar e analisar algoritmos de caminho mínimo em grafos, aplicados a um cenário específico onde um personagem fictício, "Linque", deve encontrar uma rota de fuga de uma floresta mística antes que fique completamente exausto ou perdido para sempre.

Estrutura do Projeto
O código está organizado da seguinte forma:

src/: Contém todos os arquivos de código fonte (.cpp).
include/: Contém todos os arquivos de cabeçalho (.h).
bin/: Diretório onde o executável é gerado após a compilação.
obj/: Contém os arquivos objeto (.o) gerados durante a compilação.
Algoritmos Implementados
O projeto inclui a implementação dos seguintes algoritmos:

Dijkstra: Algoritmo clássico para encontrar o caminho mais curto em grafos sem arestas de peso negativo. No contexto deste trabalho, é adaptado para considerar o consumo de energia e a utilização de portais mágicos que não consomem energia.
A*: Uma versão aprimorada do Dijkstra que utiliza uma função heurística (neste caso, a distância euclidiana até o destino) para priorizar os caminhos que parecem mais promissores.
Como Compilar e Executar
Para compilar e executar o projeto, utilize o seguinte comando na raiz do diretório do projeto:

bash
Copiar código
make all
Isto irá compilar os arquivos fonte, gerar os objetos e o executável em seus respectivos diretórios. Para executar o programa, navegue até a pasta bin e execute:

bash
Copiar código
./tp2.out
Entrada e Saída
O programa lê as informações do grafo a partir da entrada padrão (stdin). As entradas devem ser fornecidas no seguinte formato:

Primeira linha: Três inteiros n, m, e k, representando o número de vértices, arestas e portais, respectivamente.
Próximas n linhas: Coordenadas x e y de cada vértice.
Próximas m linhas: Arestas com vértices de origem e destino e o peso associado.
Próximas k linhas: Portais entre vértices com distância zero.
Última linha: Energia total disponível e número máximo de portais que podem ser utilizados.
A saída consiste em dois inteiros indicando se é possível escapar da floresta utilizando o algoritmo de Dijkstra e o algoritmo A*, respectivamente.

Documentação
A documentação completa, incluindo a descrição das estruturas de dados, metodologia e análise de complexidade, está disponível no arquivo Documentacao.pdf.
