#ifndef RUTA_H
#define RUTA_H

#include <iostream>
#include <vector> 
#include <algorithm>
#include "VRPLIBReader.h"
using namespace std;

class Ruta{
    public:

        Ruta(const VRPLIBReader & instance);

        void agregarNodo(int n, const VRPLIBReader & instance);

        int demanda() const;
        double costo() const;
        void invertir_ruta();
        void fusionar(Ruta r, double c); //PRE: las dos rutas tienen al deposito como inicio y como fin (es para Clarke & Wright). El parametro c es el costo entre los dos nodos que van a unir las rutas
        bool es_adyacente_a_d(int n); //PRE: la ruta tiene al deposito como inicio y como fin (es para Clarke & Wright)
        const vector<int>& ruta() const; //devolver los ids
        void intercambiar(Ruta & r,int i, int j, const VRPLIBReader & instance);

    private:
        vector<int> ids;  //Empieza y termina en el id del deposito. Como vamos agregando en orden que recorremos una ruta, funciona para obtener la proxima distancia a añadir
        double _costo; //El costo de la ruta solucion.
        double _demanda; //La suma de las demandas de los nodos en ids
        int _ultimo;
};
 
#endif 