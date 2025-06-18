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
        int costo() const;

        const vector<int>& ruta(); //devolver los ids

    private:
        vector<int> ids;  //Empieza y termina en el id del deposito.
        vector<int> demandas;
        int _costo; //El costo de la ruta solucion.
        int _demanda; //La suma de las demandas de los nodos en ids
};
 
#endif 