#include "campfire.h"

Campfire::Campfire(const std::string& name, double x, double y) : name(name), x(x), y(y) {}

void Campfire::addConnection(const std::string& name, int weight) {
    connections.push_back({name, weight});
}

std::string Campfire::getName() const {
    return name;
}

std::vector<Connection> Campfire::getConnections() const {
    return connections;
}

double Campfire::getX() const {
    return x;
}

double Campfire::getY() const {
    return y;
}
