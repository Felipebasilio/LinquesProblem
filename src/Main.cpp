#include <iostream>
#include <vector>
#include <cmath>  // Necessário para funções de cálculo de distância
#include "campfire.h"
#include "pathfinding.h"
#include "utils.h"

int main() {
    int numVertices, numPaths, numPortals;
    std::cin >> numVertices >> numPaths >> numPortals;

    std::vector<Campfire> graph;
    std::vector<std::pair<double, double>> coordinates; // Vetor para armazenar coordenadas de cada vértice

    double x, y;
    
    // Lendo as coordenadas das clareiras e criando os vértices
    for (int i = 0; i < numVertices; ++i) {
        std::cin >> x >> y;
        graph.emplace_back(std::to_string(i), x, y);
        coordinates.emplace_back(x, y); // Armazenando as coordenadas para cálculo posterior
    }

    int u, v;
    // Lendo as trilhas e calculando o peso baseado na distância euclidiana
    for (int i = 0; i < numPaths; ++i) {
        std::cin >> u >> v;
        double weight = calculateEuclideanDistance(coordinates[u].first, coordinates[u].second, coordinates[v].first, coordinates[v].second);
        graph[u].addConnection(std::to_string(v), weight); // adiciona conexão de u para v com o peso calculado
        // std::cout << "Adicionando conexão de trilha de " << u << " para " << v << " com peso " << weight << std::endl;
    }

    // Lendo os portais
    for (int i = 0; i < numPortals; ++i) {
        std::cin >> u >> v;
        graph[u].addConnection(std::to_string(v), 0); // Peso zero para portais
        // std::cout << "Adicionando conexão de portal de " << u << " para " << v << " com peso 0" << std::endl;
    }

    int s;
    int q;
    std::cin >> s >> q;

    // Aplicando os algoritmos de Dijkstra e A*
    // std::cout << "Resultado usando Dijkstra: ";
    dijkstra(graph, 0, s, q);

    // std::cout << "Resultado usando A*: ";
    a_star(graph, 0, numVertices - 1, s, q);

    return 0;
}
