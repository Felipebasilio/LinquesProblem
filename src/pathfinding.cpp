#include "pathfinding.h"
#include <queue>
#include <vector>
#include <cmath>
#include <limits>
#include <set>

// Estrutura auxiliar para vértices na fila de prioridade
struct Vertex {
    int id;
    int dist;
    bool operator>(const Vertex& other) const {
        return dist > other.dist;
    }
};

// Função heurística para A*
double heuristic(const Campfire& a, const Campfire& b) {
    return std::sqrt(std::pow(a.getX() - b.getX(), 2) + std::pow(a.getY() - b.getY(), 2));
}

// Implementação do algoritmo de Dijkstra
void dijkstra(const std::vector<Campfire>& graph, int src, int maxEnergy, int maxPortals) {
    std::priority_queue<Vertex, std::vector<Vertex>, std::greater<Vertex>> pq;
    std::vector<int> distances(graph.size(), std::numeric_limits<int>::max());
    std::vector<int> portalsUsed(graph.size(), 0);

    distances[src] = 0;
    pq.push({src, 0});

    while (!pq.empty()) {
        Vertex u = pq.top();
        pq.pop();

        for (const auto& connection : graph[u.id].getConnections()) {
            int v = std::stoi(connection.name);  // Assume name can be converted to int ID
            int weight = connection.weight;
            int newDist = u.dist + weight;
            int newPortals = portalsUsed[u.id] + (weight == 0 ? 1 : 0);

            if (newDist < distances[v] && newPortals <= maxPortals) {
                distances[v] = newDist;
                portalsUsed[v] = newPortals;
                pq.push({v, newDist});
            }
        }
    }

    // Output the result
    int lastVertex = graph.size() - 1;
    if (distances[lastVertex] <= maxEnergy && portalsUsed[lastVertex] <= maxPortals) {
        std::cout << "1\n";  // Linque can escape
    } else {
        std::cout << "0\n";  // Linque cannot escape
    }
}

// Implementação do algoritmo A*
void a_star(const std::vector<Campfire>& graph, int src, int dest, int maxEnergy, int maxPortals) {
    std::set<Vertex> openSet;
    std::vector<double> gScore(graph.size(), std::numeric_limits<double>::max());
    std::vector<double> fScore(graph.size(), std::numeric_limits<double>::max());
    std::vector<int> portalsUsed(graph.size(), 0);

    gScore[src] = 0;
    fScore[src] = heuristic(graph[src], graph[dest]);
    openSet.insert({src, static_cast<int>(fScore[src])});

    while (!openSet.empty()) {
        Vertex current = *openSet.begin();
        openSet.erase(openSet.begin());

        if (current.id == dest) {
            if (gScore[dest] <= maxEnergy && portalsUsed[dest] <= maxPortals) {
                std::cout << "1\n";  // Linque can escape
                return;
            }
            break;
        }

        for (const auto& connection : graph[current.id].getConnections()) {
            int neighbor = std::stoi(connection.name);
            int weight = connection.weight;
            double tentative_gScore = gScore[current.id] + weight;
            int newPortals = portalsUsed[current.id] + (weight == 0 ? 1 : 0);

            if (tentative_gScore < gScore[neighbor] && newPortals <= maxPortals) {
                gScore[neighbor] = tentative_gScore;
                fScore[neighbor] = gScore[neighbor] + heuristic(graph[neighbor], graph[dest]);
                openSet.insert({neighbor, static_cast<int>(fScore[neighbor])});
                portalsUsed[neighbor] = newPortals;
            }
        }
    }

    std::cout << "0\n";  // Linque cannot escape
}
