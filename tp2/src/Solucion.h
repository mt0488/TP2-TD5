#include "Ruta.h"

class Solucion{
    public:
        Solucion();
        void añadirRuta(Ruta r);
        int costo();

    private:
        vector<Ruta> _rutas;
        int _costo;

};