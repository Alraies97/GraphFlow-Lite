#include <iostream>
#include <string>
#include <vector>

#include "../include/GraphFlow.hpp"

int main() {
    graphflow::Graph roadNetwork;

    roadNetwork.addUndirectedEdge("Erbil", "Duhok", 160.0);
    roadNetwork.addUndirectedEdge("Duhok", "Zakho", 60.0);
    roadNetwork.addUndirectedEdge("Erbil", "Zakho", 230.0);

    const auto route = roadNetwork.dijkstra("Erbil", "Zakho");

    if (route.path.empty()) {
        std::cout << "No route found between Erbil and Zakho.\n";
        return 0;
    }

    std::cout << "Shortest route from Erbil to Zakho:\n";
    for (std::size_t i = 0; i < route.path.size(); ++i) {
        std::cout << route.path[i];
        if (i + 1 < route.path.size()) {
            std::cout << " -> ";
        }
    }
    std::cout << "\nTotal distance: " << route.distance << " km\n";

    return 0;
}
