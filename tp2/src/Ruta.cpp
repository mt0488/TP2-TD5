#include "Ruta.h"

Ruta::Ruta(const VRPLIBReader & instance){
    _costo = 0;
    _demanda = 0;
    demandas = vector<double>(instance.getDimension()+1);
    _ultimo = instance.getDepotId();
}

void Ruta::agregarNodo(int n, const VRPLIBReader & instance){
    ids.push_back(n);
    _costo += instance.getDistanceMatrix()[n][_ultimo]; //Actualizamos el costo usando la arista entre el ultimo id agregado y n  
    _demanda += instance.getDemands()[n];
    demandas[n] = instance.getDemands()[n];
    _ultimo = n;
}

int Ruta::demanda() const{
    return _demanda;
}

double Ruta::costo() const{
    return _costo;
}

const vector<int>& Ruta::ruta(){
    return ids;
}
