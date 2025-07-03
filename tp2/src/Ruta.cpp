#include "Ruta.h"


Ruta::Ruta(const VRPLIBReader & instance){
    _costo = 0;
    _demanda = 0;
    _ultimo = instance.getDepotId();
}


void Ruta::agregarNodo(int n, const VRPLIBReader & instance){
    ids.push_back(n);
    _costo += instance.getDistanceMatrix()[n][_ultimo]; //Actualizamos el costo usando la arista entre el ultimo id agregado y n  
    _demanda += instance.getDemands()[n];
    _ultimo = n;
}

int Ruta::demanda() const{
    return _demanda;
}

double Ruta::costo() const{
    return _costo;
}

const vector<int>& Ruta::ruta() const{
    return ids;
}

bool Ruta::es_adyacente_a_d(int n){
    if(ids[1]==n || ids[ids.size()-2]==n){
        return true;
    }else{
        return false;
    }
}

void Ruta::invertir_ruta(){
    reverse(ids.begin(),ids.end());
    _ultimo = ids[ids.size()-1];
}

void Ruta::fusionar(Ruta r, double c){
    _demanda += r._demanda;
    _costo = _costo + r._costo + c ;
    ids.pop_back(); // El deposito era el ultimo nodo
    r.ids.erase(r.ids.begin()); // El deposito es el primer nodo
    ids.insert(ids.end(),r.ids.begin(),r.ids.end());
    
}