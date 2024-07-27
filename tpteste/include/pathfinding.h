#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "campfire.h"
#include <vector>

void dijkstra(const std::vector<Campfire>& graph, int src, int maxEnergy, int maxPortals);
void a_star(const std::vector<Campfire>& graph, int src, int dest, int maxEnergy, int maxPortals);

#endif // PATHFINDING_H
