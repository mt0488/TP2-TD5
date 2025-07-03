#ifndef SOLUCION_H
#define SOLUCION_H

#include "Ruta.h"

class Solucion{
    public:
        Solucion();
        void añadirRuta(Ruta r);
        int costo();
        void printSolucion();
        vector<Ruta> rutas();
    private:
        vector<Ruta> _rutas;
        int _costo;

};

#endif