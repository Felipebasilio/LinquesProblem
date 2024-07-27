#ifndef CAMPFIRE_H
#define CAMPFIRE_H

#include <vector>
#include <string>

struct Connection {
    std::string from;  // Vértice de origem
    std::string to;    // Vértice de destino
    double weight;     // Peso da conexão
};

class Campfire {
public:
    Campfire(const std::string& name, double x, double y);  // Construtor atualizado

    void addConnection(const std::string& to, double weight);
    std::string getName() const;
    std::vector<Connection> getConnections() const;
    double getX() const;  // Getter para X
    double getY() const;  // Getter para Y

private:
    std::string name;                      // Nome/ID da clareira
    std::vector<Connection> connections;  // Conexões a outras clareiras
    double x, y;                           // Coordenadas da clareira
};

#endif // CAMPFIRE_H
