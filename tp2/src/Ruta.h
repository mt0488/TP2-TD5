#ifndef RUTA_H
#define RUTA_H

#include <iostream>
#include <vector> 
#include "VRPLIBReader.h"
using namespace std;

class Ruta{
    public:

        Ruta(const VRPLIBReader & instance);

        void agregarNodo(int n, const VRPLIBReader & instance);

        int demanda() const;
        double costo() const;
        void printRuta();
        const vector<int>& ruta(); //devolver los ids

    private:
        vector<int> ids;  //Empieza y termina en el id del deposito. Como vamos agregando en orden que recorremos una ruta, funciona para obtener la proxima distancia a añadir
        vector<double> demandas;
        double _costo; //El costo de la ruta solucion.
        double _demanda; //La suma de las demandas de los nodos en ids
        int _ultimo;
};
 
#endif 