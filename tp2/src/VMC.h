#ifndef VMC_H
#define VMC_H

#include <vector>
#include "Solucion.h"
// Vecino mas cercano

class VMC{

public:
    VMC();
    Solucion resolver(const VRPLIBReader & instance);


 private:
     std::vector<bool> _visitados;
    int _capacidad;
    int _autos;

};

#endif
