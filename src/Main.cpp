#include <iostream>
#include "campfire.h"

int main() {
    Campfire cf1("Clareira Central");
    cf1.addConnection("Clareira Norte", 10);
    cf1.addConnection("Clareira Sul", 0); // Portal

    // Simulação de uso
    std::cout << "Clareira: " << cf1.getName() << "\nConexões:\n";
    for (auto& conn : cf1.getConnections()) {
        std::cout << "  - " << conn.name << " com peso " << conn.weight << '\n';
    }

    return 0;
}
