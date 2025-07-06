#ifndef SOLUCION_H
#define SOLUCION_H

#include "Ruta.h"

class Solucion{
    public:
        Solucion();
        void añadirRuta(Ruta r);
        double costo();
        void printSolucion();
        vector<Ruta>& rutas();
        void recalcularCosto();
    private:
        vector<Ruta> _rutas;
        double _costo;

};

#endif