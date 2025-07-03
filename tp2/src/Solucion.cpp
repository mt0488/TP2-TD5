#include "Solucion.h"

Solucion::Solucion(){
    _rutas = {};
    _costo = 0;
}

void Solucion::añadirRuta(Ruta r){
    _rutas.push_back(r);
    _costo += r.costo();
}

int Solucion::costo(){
    return _costo;
}

void Solucion::printSolucion(){
    double costo = 0;
    for(int i = 0 ; i< _rutas.size();i++){
        for(int j = 0;j<(_rutas[i].ruta()).size();j++){
            cout<<(_rutas[i].ruta())[j]<<" ";
        }
        cout<<", Costo:"<<_rutas[i].costo()<<endl;
        costo+=_rutas[i].costo();
    }
    cout<<"Costo total:"<<costo<<endl;
}

vector<Ruta>& Solucion::rutas(){
    return _rutas;
}

void Solucion::recalcularCosto(){
    _costo=0;
    for(int i=0;i<_rutas.size();i++){
        _costo+=_rutas[i].costo();
    }
}