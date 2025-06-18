#include "Ruta.h"

Ruta::Ruta(){
    _costo = 0;
    _demanda = 0;
}

void Ruta::agregarNodo(int n, const VRPLIBReader & instance){
    ids.push_back(n);
    _demanda += instance.getDemands()[n];
    demandas[n] = instance.getDemands()[n];

    _costo += instance.getDistanceMatrix()[n][ids[ids.size()-1]]; //Actualizamos el costo usando la arista entre el ultimo id y n

}