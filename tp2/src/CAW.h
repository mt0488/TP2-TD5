#ifndef CAW_H
#define CAW_H

#include "Solucion.h"

//Clarke & Wright

class CAW{
    public:
        CAW();
        Solucion resolver(const VRPLIBReader & instance);

    private:
        vector<pair<int,int>> _par;
        vector<double>  _ahorros;
        int _capacidad;
};


#endif