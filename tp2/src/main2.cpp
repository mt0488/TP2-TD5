#include "VMC.h"
#include "CAW.h"
#include "swap.h"
#include <iostream>
using namespace std;


int main(){

    VRPLIBReader instance("/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E021-04m.dat");

    CAW test;
    Solucion s = test.resolver(instance);
    s.printSolucion();

    cout<<endl;
    swapRutas(s,instance);
    s.printSolucion();
    return 0;
}