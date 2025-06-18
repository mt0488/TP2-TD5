#include "VMC.h"
#include <limits>

VMC::VMC(){}

Solucion VMC::resolver(const VRPLIBReader& instance){
    Solucion sol;
    _capacidad = instance.getCapacity();
    _autos = instance.getNumVehicles();
    _visitados = std::vector<bool>(instance.getDimension() + 1, false);
    int depot = instance.getDepotId();
    _visitados[depot] = true;

    const auto& dist = instance.getDistanceMatrix();
    int remaining = instance.getDimension() - 1; // excluding depot

    while (remaining > 0) {
        Ruta ruta(instance);
        ruta.agregarNodo(depot, instance);
        int capacidadRestante = _capacidad;
        int actual = depot;
        while (true) {
            int mejor = -1;
            double mejorDist = std::numeric_limits<double>::infinity();
            for (int i = 1; i <= instance.getDimension(); ++i) {
                if (!_visitados[i] && instance.getDemands()[i] <= capacidadRestante) {
                    if (dist[actual][i] < mejorDist) {
                        mejorDist = dist[actual][i];
                        mejor = i;
                    }
                }
            }
            if (mejor == -1) {
                break;
            }
            ruta.agregarNodo(mejor, instance);
            capacidadRestante -= instance.getDemands()[mejor];
            _visitados[mejor] = true;
            actual = mejor;
            --remaining;
        }
        ruta.agregarNodo(depot, instance);
        sol.añadirRuta(ruta);
    }

    return sol;
}


