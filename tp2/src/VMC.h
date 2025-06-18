#ifndef VMC_H
#define VMC_H

#include "Solucion.h"
// Vecino mas cercano

class VMC{

public:
    VMC();
    Solucion resolver(const VRPLIBReader & instance);


private:
    vector<bool> _visitados;
    int _capacidad;
    int _autos;
    void vmc(Solucion & s, Ruta & r, const VRPLIBReader & instace);

};

#endif