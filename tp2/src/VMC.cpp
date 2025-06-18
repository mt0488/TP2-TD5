#include "VMC.h"

VMC::VMC(){}

Solucion VMC::resolver(const VRPLIBReader & instance){
    Solucion sol;
    _capacidad = instance.getCapacity();
    _autos = instance.getNumVehicles();
    _visitados = vector<bool>(instance.getDimension(),false);
    _visitados[instance.getDepotId()-1] = true;
    
}