#include "Solucion.h"
#include <iostream>
#include <cassert>
using namespace std;

//Dado que ya se implementó un testing para la clase Ruta, no es necesario volver a usar todos sus métodos en este, 
//solo los necesarios para asegurar el funcionamiento de Solucion

//Para el test se usará la misma instancia: E016-03m
VRPLIBReader instance("/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E016-03m.dat");

int main(){
    //Añadir una sola ruta
    {
        Ruta r(instance);
        r.agregarNodo(1,instance);
        r.agregarNodo(2,instance);
        r.agregarNodo(3,instance);
        r.agregarNodo(4,instance);
        r.agregarNodo(1,instance);

        Solucion s;
        s.añadirRuta(r);
        assert(s.costo()==r.costo());
        assert(s.rutas().size()==1);
        assert(s.rutas()[0].ruta()[1]==r.ruta()[1]);
        cout<<"Añadir una ruta ✓"<<endl;
    }

    return 0;
}