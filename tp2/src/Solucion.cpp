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

