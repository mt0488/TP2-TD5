#include <iostream>
#include <string>
#include "VRPLIBReader.h"
#include "Heuristics.h"

void printSolution(const Solution& sol) {
    std::cout << "Total cost: " << sol.totalCost << "\n";
    for (size_t i = 0; i < sol.routes.size(); ++i) {
        std::cout << "Route " << i+1 << ": ";
        for (int node : sol.routes[i].nodes) {
            std::cout << node << ' ';
        }
        std::cout << "| load=" << sol.routes[i].load << " cost=" << sol.routes[i].cost << '\n';
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_vrp_file> [cw|nn]" << std::endl;
        return 1;
    }

    std::cerr << "Reading instance...\n";
    VRPLIBReader reader(argv[1]);
    std::string method = argc >= 3 ? argv[2] : "cw";
    Solution sol;

    std::cerr << "Constructing initial solution using " << method << "...\n";
    if (method == "cw") {
        sol = clarkeWright(reader);
    } else if (method == "nn") {
        sol = nearestNeighbor(reader);
    } else {
        std::cerr << "Unknown method: " << method << std::endl;
        return 1;
    }

    std::cerr << "Initial cost: " << sol.totalCost << "\n";

    std::cerr << "Starting local search...\n";
    bool improved = true;
    int iter = 0;
    while (improved && iter < 100) {
        improved = false;
        if (relocate(sol, reader)) improved = true;
        if (swapNodes(sol, reader)) improved = true;
        ++iter;
    }
    std::cerr << "Local search iterations: " << iter << "\n";

    printSolution(sol);
    return 0;
}
