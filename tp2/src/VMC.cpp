#include "VMC.h"

VMC::VMC(){}

int VMC::masCercano(int n, const VRPLIBReader & instance){
    int v = -1;
    double d = 1e6 ;
    for(auto i:instance.getNodes()){
        if(i.id!=n && !_visitados[i.id] && instance.getDistanceMatrix()[n][i.id]<d){
            v = i.id;
            d = instance.getDistanceMatrix()[n][i.id];
        }
    }
    
    return v;
}

void VMC::vmc(Solucion & s,  const VRPLIBReader & instance){
    int actual = instance.getDepotId();
    Ruta r(instance);
    r.agregarNodo(actual,instance);
    int i = 0;
    while(i < _autos && actual!=-1){
        int w = masCercano(actual,instance);
        if(w==-1){ //Todos los nodos fueron visitados
            r.agregarNodo(instance.getDepotId(),instance);
            s.añadirRuta(r);
            actual = w;
        } else if(r.demanda()+instance.getDemands()[w]>_capacidad){ //No se puede añadir mas
            r.agregarNodo(instance.getDepotId(),instance); // Se cierra la ruta
            i++; //Hay que agregar otro auto
            s.añadirRuta(r);
            actual = instance.getDepotId();
            r = Ruta(instance); //Inicia una nueva ruta
            r.agregarNodo(actual,instance);
            
        }else{
            r.agregarNodo(w,instance);
            actual = w;
            _visitados[w] = true;
        }
        
    }
}

Solucion VMC::resolver(const VRPLIBReader & instance){
    Solucion sol;
    _capacidad = instance.getCapacity();
    _autos = instance.getNumVehicles();
    
    _visitados = vector<bool>(instance.getDimension()+1,false);
    _visitados[instance.getDepotId()] = true; 

    vmc(sol,instance);
    return sol;
}