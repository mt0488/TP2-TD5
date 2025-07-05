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
    _costo = _costo + r._costo + c ; //Costo ruta1+costo ruta 2 - ahorro
    ids.pop_back(); // El deposito era el ultimo nodo
    r.ids.erase(r.ids.begin()); // El deposito es el primer nodo
    ids.insert(ids.end(),r.ids.begin(),r.ids.end());
    
}

void Ruta::intercambiar(Ruta & r,int i, int j, const VRPLIBReader & instance){
    int temp=ids[i];
    ids[i]=r.ids[j];
    r.ids[j]=temp;

    //recalcular el costo y demanda
    _demanda=0;
    _costo = 0;
    for (int i = 0; i < ids.size() - 1; ++i) {
        _costo += instance.getDistanceMatrix()[ids[i]][ids[i + 1]];
        _demanda +=instance.getDemands()[ids[i]];
    }

    r._costo=0;
    r._demanda=0;
    for (int i = 0; i < r.ids.size() - 1; ++i) {
        r._costo += instance.getDistanceMatrix()[r.ids[i]][r.ids[i + 1]];
        r._demanda += instance.getDemands()[r.ids[i]];
    }
}

void Ruta::insertar(Ruta& origen, int idx_origen, int idx_destino, const VRPLIBReader& instance) {
    int n = origen.ids[idx_origen];
    ids.insert(ids.begin() + idx_destino, n);

    //recalculamos costo y demanda de esta ruta
    _demanda += instance.getDemands()[n];
    _costo = 0;
    for (int i = 0; i < ids.size() - 1; ++i) {
        _costo += instance.getDistanceMatrix()[ids[i]][ids[i + 1]];
    }

    //eliminamos el cliente de la ruta origen
    origen.ids.erase(origen.ids.begin() + idx_origen);
    
    // recalculamos costo de la ruta origen
    origen._demanda -= instance.getDemands()[n];
    origen._costo = 0;
    for (int i = 0; i < origen.ids.size() - 1; ++i) {
        origen._costo += instance.getDistanceMatrix()[origen.ids[i]][origen.ids[i + 1]];
    }
}
