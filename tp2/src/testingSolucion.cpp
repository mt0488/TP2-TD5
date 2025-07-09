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
        assert(s.rutas()[0].ruta()[1]==r.ruta()[1] && s.rutas()[0].ruta()[2]==r.ruta()[2] && s.rutas()[0].ruta()[3]==r.ruta()[3]);

        cout<<"Añadir una ruta ✓"<<endl;
    }

    //Añadir varias rutas
    {
        Ruta r1(instance); r1.agregarNodo(1,instance);r1.agregarNodo(2,instance); r1.agregarNodo(3,instance);r1.agregarNodo(1,instance);
        Ruta r2(instance); r2.agregarNodo(1,instance);r2.agregarNodo(4,instance); r2.agregarNodo(5,instance);r2.agregarNodo(1,instance);
        Ruta r3(instance); r3.agregarNodo(1,instance);r3.agregarNodo(6,instance); r3.agregarNodo(7,instance);r3.agregarNodo(1,instance);

        Solucion s;
        s.añadirRuta(r1);s.añadirRuta(r2);s.añadirRuta(r3);

        assert(s.rutas().size() == 3);
        assert(s.costo() == (r1.costo()+r2.costo()+r3.costo()));
        assert(s.rutas()[0].ruta()[1]==r1.ruta()[1] && s.rutas()[1].ruta()[1]==r2.ruta()[1] && s.rutas()[2].ruta()[1]==r3.ruta()[1]);
        
        cout<<"Añadir varias rutas ✓"<<endl;
    }

    return 0;
}