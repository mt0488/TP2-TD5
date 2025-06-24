#include "VMC.h"
#include <iostream>
using namespace std;


int main(){

    VRPLIBReader instance("/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E021-04m.dat");
    
    VMC test;
    Solucion s = test.resolver(instance);
    s.printSolucion();
    return 0;
}