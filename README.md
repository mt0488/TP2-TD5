# TP2-TD5

This repository includes a small C++ project for solving CVRP instances in VRPLIB format.

## Compilation

From the `tp2/src` directory compile using:

```bash
g++ -std=c++11 -O2 -o vrp_solver main.cpp VRPLIBReader.cpp Heuristics.cpp
```

## Usage

Run the solver providing the instance file and optionally the heuristic method (`cw` for Clarke & Wright or `nn` for nearest neighbour):

```bash
./vrp_solver path/to/instance.dat cw
```

After constructing a solution the program applies simple local search (relocate and swap) until no improvement is found and prints the resulting routes and total cost.
