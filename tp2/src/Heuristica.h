#ifndef HEURISTICA_H
#define HEURISTICA_H


#include <iostream>
#include "Solucion.h"


class Heuristica{
    public:

        Solucion vmc(const VRPLIBReader & instance); //Vecino mas cercano
        Solucion caw(const VRPLIBReader & instance); //Clark and Wright
        void relocate(Solucion & s, const VRPLIBReader & instance);
        void swap_();

    private:

};

#endif