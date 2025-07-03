#include "VMC.h"

VMC::VMC(){}

int VMC::masCercano(int n, const VRPLIBReader & instance){
    int v = -1;
    double d = 1e6 ;
    for(auto i:instance.getNodes()){

        if(i.id!=n && !_visitados[i.id] && instance.getDistanceMatrix()[n][i.id]<d && instance.getDemands()[i.id]<=_capacidad){
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
    int i = 0; //Para la cantidad de autos
    int j =0; //Para ver si ya se visitaron todos los nodos, porque de ser así se pueden ahorrar autos

    while(i < _autos){
        if(j==instance.getDimension()-1){ //Ya se visitaron todos los nodos, podemos ahorrar autos
            r.agregarNodo(instance.getDepotId(),instance); // Se cierra la ruta
            s.añadirRuta(r);
            break;
        }
        int w = masCercano(actual,instance);
        if(w==-1){ 
            r.agregarNodo(instance.getDepotId(),instance); // Se cierra la ruta
            i++; //Hay que agregar otro auto
            s.añadirRuta(r);
            actual = instance.getDepotId(); //Empezamos a recorrer el grafo otra vez desde el deposito
            _capacidad = instance.getCapacity();
            r = Ruta(instance); //Inicia una nueva ruta
            r.agregarNodo(actual,instance);
        }else{
            r.agregarNodo(w,instance);
            actual = w;
            _capacidad -= instance.getDemands()[w];
            _visitados[w] = true;
            j++;
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