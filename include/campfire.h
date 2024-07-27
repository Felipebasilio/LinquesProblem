#ifndef CAMPFIRE_H
#define CAMPFIRE_H

#include <vector>
#include <string>

// Estrutura para representar conexões para outras clareiras
struct Connection {
    std::string name;  // Nome/ID da clareira de destino
    int weight;        // Peso da trilha, 0 para portal
};

// Classe que representa uma clareira
class Campfire {
public:
    Campfire(const std::string& name, double x, double y);
    void addConnection(const std::string& name, int weight);
    std::string getName() const;
    std::vector<Connection> getConnections() const;
    double getX() const;
    double getY() const;

private:
    std::string name;               // Nome/ID da clareira
    std::vector<Connection> connections;  // Conexões a outras clareiras
    double x, y;                    // Coordenadas da clareira no plano
};

#endif // CAMPFIRE_H
