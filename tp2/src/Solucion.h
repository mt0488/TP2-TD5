#ifndef SOLUCION_H
#define SOLUCION_H

#include <vector>
#include "Ruta.h"

class Solucion{
    public:
        Solucion();
        void añadirRuta(Ruta r);
        int costo() const;
        const std::vector<Ruta>& rutas() const { return _rutas; }

    private:
        std::vector<Ruta> _rutas;
        int _costo;
};

#endif
