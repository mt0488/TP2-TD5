#include "GRASP.h"

GRASP::GRASP(){}

int GRASP::masCercano(int n, const VRPLIBReader & instance){
    vector<int> vecinos;
    vector<double> distancias;
    for(auto i:instance.getNodes()){
        if(i.id!=n && !_visitados[i.id] && instance.getDemands()[i.id]<=_capacidad){
            vecinos.push_back(i.id);
            distancias.push_back(instance.getDistanceMatrix()[i.id][n]);
        }
    }
    
    for(int i=0;i<vecinos.size();i++){
        double min=distancias[i];
        int pos = i;
        for(int j=i+1;j<vecinos.size();j++){
            if(distancias[j]<min){
                min=distancias[j];
                pos=j;
            }
        }
        swap(vecinos[i],vecinos[pos]);
        swap(distancias[i],distancias[pos]);
    }
    vector<int> candidatos;
    for (int i = 0; i < vecinos.size() && i < _rcl; i++) {
        candidatos.push_back(vecinos[i]);
    }
    if(candidatos.empty()) return -1;

    srand(time(0)); 
    int elegir = rand() % (candidatos.size());

    return candidatos[elegir];
}

void GRASP::vmc(Solucion & s,  const VRPLIBReader & instance){
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

Solucion GRASP::resolver(int rcl,int iters,const VRPLIBReader & instance){
    Solucion sol;
    _capacidad = instance.getCapacity();
    _autos = instance.getNumVehicles();
    _rcl=rcl;
    _visitados = vector<bool>(instance.getDimension()+1,false);
    _visitados[instance.getDepotId()] = true; 

    vmc(sol,instance); //Resolvemos una primera vez para poder comparar las siguientes soluciones con alguna ya existente

    for(int i = 0;i<iters;i++){
        Solucion st;
        _visitados = vector<bool>(instance.getDimension() + 1, false);
        _visitados[instance.getDepotId()] = true;
        _capacidad=instance.getCapacity();
        vmc(st,instance);
        swapRutas(st,instance);
        if(st.costo()<sol.costo()){
            sol=st;
        }
    }

    return sol;
}