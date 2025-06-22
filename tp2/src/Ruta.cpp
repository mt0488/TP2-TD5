#include "Ruta.h"

Ruta::Ruta(const VRPLIBReader & instance){
    _costo = 0;
    _demanda = 0;
    demandas = vector<int>(instance.getDimension());
}

void Ruta::agregarNodo(int n, const VRPLIBReader & instance){
    _costo += instance.getDistanceMatrix()[n][ids[ids.size()-1]]; //Actualizamos el costo usando la arista entre el ultimo id agregado y n  
    ids.push_back(n);
    _demanda += instance.getDemands()[n];
    demandas[n] = instance.getDemands()[n];
}

int Ruta::demanda() const{
    return _demanda;
}

int Ruta::costo() const{
    return _costo;
}

const vector<int>& Ruta::ruta(){
    return ids;
}