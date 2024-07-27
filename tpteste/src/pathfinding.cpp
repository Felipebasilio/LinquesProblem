#include "pathfinding.h"
#include "campfire.h"
#include "utils.h"

#include <queue>
#include <vector>
#include <cmath>
#include <limits>
#include <set>
#include <iostream>
#include <climits>

// Estrutura auxiliar para vértices na fila de prioridade
struct Vertex {
    int id;
    double distance;

    // Operador < necessário para std::set e ordenação padrão
    bool operator<(const Vertex& other) const {
        return distance < other.distance || (distance == other.distance && id < other.id);
    }

    // Operador > para ordenação inversa, usado em std::priority_queue quando especificado
    bool operator>(const Vertex& other) const {
        return distance > other.distance || (distance == other.distance && id > other.id);
    }
};

// Função heurística para A*
double heuristic(const Campfire& a, const Campfire& b) {
    double h = std::sqrt(std::pow(a.getX() - b.getX(), 2) + std::pow(a.getY() - b.getY(), 2));
    // std::cout << "Heurística entre " << a.getName() << " e " << b.getName() << ": " << h << std::endl;
    return h;
}

void printGraph(const std::vector<Campfire>& graph) {
    std::cout << "Visualização do Grafo:\n";
    for (const auto& campfire : graph) {
        std::cout << "Clareira " << campfire.getName() << " possui conexões:\n";
        for (const auto& connection : campfire.getConnections()) {
            std::cout << "  -> Conecta a " << connection.to 
                      << " com peso " << connection.weight << "\n";
        }
    }
}

// Implementação do algoritmo de Dijkstra
void dijkstra(const std::vector<Campfire>& graph, int sourceVertex, int maxEnergy, int maxPortalUsages) {
    std::priority_queue<Vertex, std::vector<Vertex>, std::greater<Vertex>> priorityQueue;
    std::vector<double> shortestDistances(graph.size(), std::numeric_limits<double>::max());
    std::vector<int> portalUsages(graph.size(), 0);

    shortestDistances[sourceVertex] = 0;
    priorityQueue.push({sourceVertex, 0});
    // std::cout << "Dijkstra inicializado: Partindo da clareira " << sourceVertex << std::endl;

    while (!priorityQueue.empty()) {
        Vertex current = priorityQueue.top();
        priorityQueue.pop();

        if (current.distance > shortestDistances[current.id]) continue;  // Ignore stale distances in the priority queue

        for (const auto& connection : graph[current.id].getConnections()) {
            int neighbor = std::stoi(connection.to);
            double weight = (connection.weight == 0) ? 0 : calculateEuclideanDistance(
                graph[current.id].getX(), graph[current.id].getY(),
                graph[neighbor].getX(), graph[neighbor].getY()
            );

            double newDistance = current.distance + weight;
            int newPortalUsages = portalUsages[current.id] + (weight == 0 ? 1 : 0);

            if (newDistance < shortestDistances[neighbor] || newPortalUsages < portalUsages[neighbor]) {
                shortestDistances[neighbor] = newDistance;
                portalUsages[neighbor] = newPortalUsages;
                priorityQueue.push({neighbor, newDistance});
                // std::cout << "Atualizando distância para clareira " << neighbor << " para " << newDistance << std::endl;
            }
        }
    }

    int destinationVertex = graph.size() - 1;
    if (shortestDistances[destinationVertex] <= maxEnergy && portalUsages[destinationVertex] <= maxPortalUsages) {
        // std::cout << "1 - Linque pode escapar\n";
        std::cout << "1 ";
    } else {
        // std::cout << "0 - Linque não pode escapar\n";
        std::cout << "0 ";
    }
}

// Implementação do algoritmo A*
void a_star(const std::vector<Campfire>& graph, int src, int dest, int maxEnergy, int maxPortals) {
    std::priority_queue<Vertex, std::vector<Vertex>, std::greater<Vertex>> openQueue;
    std::vector<double> gScore(graph.size(), std::numeric_limits<double>::max());
    std::vector<double> fScore(graph.size(), std::numeric_limits<double>::max());
    std::vector<int> portalsUsed(graph.size(), 0);

    gScore[src] = 0;
    fScore[src] = heuristic(graph[src], graph[dest]);
    openQueue.push({src, fScore[src]});
    // std::cout << "A* inicializado: Partindo de " << src << " para " << dest << std::endl;

    while (!openQueue.empty()) {
        Vertex current = openQueue.top();
        openQueue.pop();

        if (current.id == dest) {
            if (gScore[dest] <= maxEnergy && portalsUsed[dest] <= maxPortals) {
                // std::cout << "1 - Linque pode escapar\n";
                std::cout << "1 ";
                return;
            }
            break;
        }

        for (const auto& connection : graph[current.id].getConnections()) {
            int neighbor = std::stoi(connection.to);
            double weight = connection.weight == 0 ? 0 : calculateEuclideanDistance(
                graph[current.id].getX(), graph[current.id].getY(),
                graph[neighbor].getX(), graph[neighbor].getY()
            );
            double tentative_gScore = gScore[current.id] + weight;
            if (tentative_gScore < gScore[neighbor]) {
                gScore[neighbor] = tentative_gScore;
                fScore[neighbor] = gScore[neighbor] + heuristic(graph[neighbor], graph[dest]);
                openQueue.push({neighbor, fScore[neighbor]});
            }
        }
    }

    // std::cout << "0 - Linque não pode escapar\n";
    std::cout << "0 " << std::endl;
}