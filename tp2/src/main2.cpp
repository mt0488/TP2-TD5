#include "VMC.h"
#include "CAW.h"
#include "swap.h"
#include "relocate.h"
#include "GRASP.h"
#include <iostream>
using namespace std;


int main(){

    VRPLIBReader instance("/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E016-03m.dat");

    GRASP test;
    Solucion s = test.resolver(5,10,instance);
    s.printSolucion();
    cout<<endl;
    VMC test2;
    Solucion s2 = test2.resolver(instance);
    s2.printSolucion();
    return 0;
}