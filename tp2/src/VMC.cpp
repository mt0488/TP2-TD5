#include "VMC.h"

VMC::VMC(){}

void VMC::vmc(Solucion & s, Ruta & r, const VRPLIBReader & instace){

}

Solucion VMC::resolver(const VRPLIBReader & instance){
    Solucion sol;
    _capacidad = instance.getCapacity();
    _autos = instance.getNumVehicles();
    _visitados = vector<bool>(instance.getDimension(),false);
    _visitados[instance.getDepotId()-1] = true;

    Ruta r(instance);
    r.agregarNodo(instance.getDepotId(),instance);
    
    vmc(sol,r,instance);
    return sol;
}