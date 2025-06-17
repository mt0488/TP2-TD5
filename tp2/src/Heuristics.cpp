#include "Heuristics.h"
#include <algorithm>
#include <limits>

static double dist(const VRPLIBReader& r, int i, int j) {
    const auto& m = r.getDistanceMatrix();
    return m[i][j];
}

// Clarke & Wright savings heuristic
Solution clarkeWright(const VRPLIBReader& reader) {
    Solution sol;
    int n = reader.getDimension();
    int Q = reader.getCapacity();
    int depot = reader.getDepotId();

    // initial routes: one per customer
    std::vector<Route> routes(n);
    for (int i = 1; i <= n; ++i) {
        if (i == depot) continue;
        Route r;
        r.nodes = {depot, i, depot};
        r.load = reader.getDemands()[i];
        r.cost = dist(reader, depot, i) + dist(reader, i, depot);
        sol.routes.push_back(r);
    }

    // compute savings
    struct Saving { int i; int j; double val; };
    std::vector<Saving> savings;
    for (int i = 1; i <= n; ++i) {
        if (i == depot) continue;
        for (int j = i+1; j <= n; ++j) {
            if (j == depot) continue;
            double val = dist(reader, depot, i) + dist(reader, depot, j) - dist(reader, i, j);
            savings.push_back({i, j, val});
        }
    }
    std::sort(savings.begin(), savings.end(), [](const Saving& a, const Saving& b){ return a.val > b.val; });

    // mapping from customer to route index and position
    std::vector<int> route_of(n+1, -1);
    for (size_t idx = 0; idx < sol.routes.size(); ++idx) {
        int cust = sol.routes[idx].nodes[1];
        route_of[cust] = idx;
    }

    for (const auto& s : savings) {
        int i = s.i, j = s.j;
        int ri = route_of[i];
        int rj = route_of[j];
        if (ri == rj || ri == -1 || rj == -1) continue;
        Route& R1 = sol.routes[ri];
        Route& R2 = sol.routes[rj];

        if (R1.nodes[R1.nodes.size()-2] != i) continue; // i at end of route1
        if (R2.nodes[1] != j) continue; // j at start of route2
        if (R1.load + R2.load > Q) continue;

        // merge R2 into R1
        R1.nodes.pop_back(); // remove depot at end
        R1.nodes.insert(R1.nodes.end(), R2.nodes.begin()+1, R2.nodes.end());
        R1.load += R2.load;
        R1.cost = R1.cost + R2.cost - dist(reader, depot, i) - dist(reader, depot, j) + dist(reader, i, j);

        // mark all customers in R2 to route ri
        for (size_t pos = 1; pos < R2.nodes.size()-1; ++pos)
            route_of[R2.nodes[pos]] = ri;
        R2.nodes.clear();
        R2.load = 0;
        R2.cost = 0.0;
    }

    // remove empty routes and compute total cost
    sol.routes.erase(std::remove_if(sol.routes.begin(), sol.routes.end(), [](const Route& r){ return r.nodes.empty(); }), sol.routes.end());
    sol.totalCost = 0.0;
    for (const auto& r : sol.routes) sol.totalCost += r.cost;
    return sol;
}

// nearest neighbor heuristic with capacity
Solution nearestNeighbor(const VRPLIBReader& reader) {
    Solution sol;
    int n = reader.getDimension();
    int Q = reader.getCapacity();
    int depot = reader.getDepotId();
    std::vector<bool> visited(n+1, false);
    visited[depot] = true;
    int remaining = n - 1;
    const auto& demand = reader.getDemands();

    while (remaining > 0) {
        Route r;
        r.nodes.push_back(depot);
        r.load = 0;
        int current = depot;
        while (true) {
            double bestDist = std::numeric_limits<double>::max();
            int best = -1;
            for (int i = 1; i <= n; ++i) {
                if (!visited[i] && r.load + demand[i] <= Q) {
                    double d = dist(reader, current, i);
                    if (d < bestDist) {
                        bestDist = d;
                        best = i;
                    }
                }
            }
            if (best == -1) break;
            visited[best] = true;
            --remaining;
            r.nodes.push_back(best);
            r.load += demand[best];
            r.cost += dist(reader, current, best);
            current = best;
        }
        r.nodes.push_back(depot);
        r.cost += dist(reader, current, depot);
        sol.routes.push_back(r);
        sol.totalCost += r.cost;
    }
    return sol;
}

// local search: relocate (first improvement)
bool relocate(Solution& sol, const VRPLIBReader& reader) {
    int Q = reader.getCapacity();
    const auto& demand = reader.getDemands();
    for (size_t r1 = 0; r1 < sol.routes.size(); ++r1) {
        for (size_t i = 1; i + 1 < sol.routes[r1].nodes.size(); ++i) {
            int node = sol.routes[r1].nodes[i];
            int d = demand[node];
            for (size_t r2 = 0; r2 < sol.routes.size(); ++r2) {
                if (r1 == r2) continue;
                if (sol.routes[r2].load + d > Q) continue;
                for (size_t j = 1; j < sol.routes[r2].nodes.size(); ++j) {
                    // compute cost difference
                    int prev1 = sol.routes[r1].nodes[i-1];
                    int next1 = sol.routes[r1].nodes[i+1];
                    double oldCost1 = dist(reader, prev1, node) + dist(reader, node, next1);
                    double newCost1 = dist(reader, prev1, next1);

                    int prev2 = sol.routes[r2].nodes[j-1];
                    int next2 = sol.routes[r2].nodes[j];
                    double oldCost2 = dist(reader, prev2, next2);
                    double newCost2 = dist(reader, prev2, node) + dist(reader, node, next2);

                    double delta = (newCost1 + newCost2) - (oldCost1 + oldCost2);
                    if (delta < -1e-6) {
                        // perform move
                        sol.routes[r1].nodes.erase(sol.routes[r1].nodes.begin()+i);
                        sol.routes[r1].load -= d;
                        sol.routes[r1].cost += newCost1 - oldCost1;

                        sol.routes[r2].nodes.insert(sol.routes[r2].nodes.begin()+j, node);
                        sol.routes[r2].load += d;
                        sol.routes[r2].cost += newCost2 - oldCost2;

                        sol.totalCost += delta;
                        // remove route if empty (only depot)
                        if (sol.routes[r1].nodes.size() <= 2) {
                            sol.routes.erase(sol.routes.begin()+r1);
                        }
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// local search: swap two nodes (first improvement)
bool swapNodes(Solution& sol, const VRPLIBReader& reader) {
    const auto& demand = reader.getDemands();
    int Q = reader.getCapacity();
    for (size_t r1 = 0; r1 < sol.routes.size(); ++r1) {
        for (size_t i = 1; i + 1 < sol.routes[r1].nodes.size(); ++i) {
            int node1 = sol.routes[r1].nodes[i];
            int d1 = demand[node1];
            for (size_t r2 = r1; r2 < sol.routes.size(); ++r2) {
                size_t jstart = (r1 == r2) ? i+1 : 1;
                for (size_t j = jstart; j + 1 < sol.routes[r2].nodes.size(); ++j) {
                    int node2 = sol.routes[r2].nodes[j];
                    int d2 = demand[node2];
                    if (r1 != r2 && (sol.routes[r1].load - d1 + d2 > Q || sol.routes[r2].load - d2 + d1 > Q))
                        continue;
                    // cost change
                    int prev1 = sol.routes[r1].nodes[i-1];
                    int next1 = sol.routes[r1].nodes[i+1];
                    int prev2 = sol.routes[r2].nodes[j-1];
                    int next2 = sol.routes[r2].nodes[j+1];
                    double oldCost = dist(reader, prev1, node1) + dist(reader, node1, next1) +
                                     dist(reader, prev2, node2) + dist(reader, node2, next2);
                    double newCost = dist(reader, prev1, node2) + dist(reader, node2, next1) +
                                     dist(reader, prev2, node1) + dist(reader, node1, next2);
                    double delta = newCost - oldCost;
                    if (delta < -1e-6) {
                        std::swap(sol.routes[r1].nodes[i], sol.routes[r2].nodes[j]);
                        sol.routes[r1].load = sol.routes[r1].load - d1 + d2;
                        sol.routes[r2].load = sol.routes[r2].load - d2 + d1;
                        sol.routes[r1].cost += (dist(reader, prev1, node2) + dist(reader, node2, next1)) -
                                              (dist(reader, prev1, node1) + dist(reader, node1, next1));
                        sol.routes[r2].cost += (dist(reader, prev2, node1) + dist(reader, node1, next2)) -
                                              (dist(reader, prev2, node2) + dist(reader, node2, next2));
                        sol.totalCost += delta;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

