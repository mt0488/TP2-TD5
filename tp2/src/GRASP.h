#ifndef GRASP_H
#define GRASP_H

#include <cstdlib>
#include <ctime>
#include "Solucion.h"
#include "swap.h"

class GRASP{
    public:
        GRASP();
        Solucion resolver(int rcl,int iters,const VRPLIBReader & instance);
    private:
        vector<bool> _visitados;
        int _capacidad;
        int _autos;
        int _rcl;
        void vmc(Solucion & s, const VRPLIBReader & instace);
        int masCercano(int n, const VRPLIBReader & instance);
};


#endif

//Este GRASP utiliza como heuristica vecino mas cercano y como operador local swap