#include "VMC.h"
#include "CAW.h"
#include "swap.h"
#include "relocate.h"
#include <iostream>
using namespace std;


int main(){

    VRPLIBReader instance("/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E016-05m.dat");

    VMC test;
    Solucion s = test.resolver(instance);
    s.printSolucion();

    cout<<endl;
    relocate(s,instance);
    s.printSolucion();
    return 0;
}