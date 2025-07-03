#include "VMC.h"
#include "CAW.h"
#include "swap.h"
#include "relocate.h"
#include "GRASP.h"
#include <iostream>
using namespace std;


int main(){

    VRPLIBReader instance("/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E016-05m.dat");

    GRASP test;
    Solucion s = test.resolver(4,1000,instance);
    s.printSolucion();
    
    return 0;
}