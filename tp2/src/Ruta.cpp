#include "Ruta.h"

Ruta::Ruta(){
    _costo = 0;
    _demanda = 0;
}

void Ruta::agregarNodo(int n, const VRPLIBReader & instance){
    ids.push_back(n);
    _costo += instance.getDemands()[n];
}