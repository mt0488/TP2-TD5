#ifndef CVRP_SOLUTION_H
#define CVRP_SOLUTION_H

#include <vector>

struct Route {
    std::vector<int> nodes; // sequence of node IDs including depot at start and end
    int load = 0;
    double cost = 0.0;
};

struct Solution {
    std::vector<Route> routes;
    double totalCost = 0.0;
};

#endif // CVRP_SOLUTION_H
