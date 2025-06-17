#ifndef VMC_H
#define VMC_H

#include "Solucion.h"
// Vecino mas cercano

class VMC{

public:
    VMC();
    Solucion resolver(const VRPLIBReader & instance);


private:
};

#endif