#include "Ruta.h"

Ruta::Ruta(const VRPLIBReader& instance) {
    _costo = 0;
    _demanda = 0;
    demandas = std::vector<int>(instance.getDimension() + 1, 0);
}

void Ruta::agregarNodo(int n, const VRPLIBReader& instance) {
    if (!ids.empty()) {
        _costo += instance.getDistanceMatrix()[ids.back()][n];
    }
    ids.push_back(n);
    _demanda += instance.getDemands()[n];
    if (n < static_cast<int>(demandas.size()))
        demandas[n] = instance.getDemands()[n];
}

int Ruta::demanda() const {
    return _demanda;
}

int Ruta::costo() const {
    return _costo;
}

const std::vector<int>& Ruta::ruta() const {
    return ids;
}

