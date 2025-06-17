#ifndef HEURISTICS_H
#define HEURISTICS_H

#include "VRPLIBReader.h"
#include "CVRPSolution.h"

// Clarke & Wright savings heuristic
Solution clarkeWright(const VRPLIBReader& reader);

// Simple nearest neighbor heuristic
Solution nearestNeighbor(const VRPLIBReader& reader);

// Local search operators
bool relocate(Solution& sol, const VRPLIBReader& reader);
bool swapNodes(Solution& sol, const VRPLIBReader& reader);

#endif // HEURISTICS_H
