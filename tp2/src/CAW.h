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
        vector<double>  _ahorros; //_par[i] se corresponde con _ahorros[i], el ahorro que generan los nodos j,k
        vector<Ruta> rutas_iniciales;
        int _capacidad;
        int depot;
};


#endif