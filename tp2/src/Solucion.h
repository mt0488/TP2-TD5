#include "Ruta.h"

class Solucion{
    public:
        Solucion();
        int costo();

    private:
        vector<Ruta> _rutas;
        int _costo;

};