#include "Ruta.h"
#include <iostream>
#include <cassert>
using namespace std;

//Para el test se usará la misma instancia: E016-03m
VRPLIBReader instance("/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E016-03m.dat");

int main(){

    //Constructor
    {
        Ruta r(instance);
        double costo = r.costo();
        double demanda = r.demanda();

        assert(costo==0.0);
        cout<<"Costo inicial ✓"<<endl;

        assert(demanda==0.0);
        cout<<"Demanda inicial ✓"<<endl;

        
    }
    
    //Agregar un nodo (la distancia se cuenta desde el depósito)
    {
        Ruta r(instance);
        r.agregarNodo(2,instance);
        double costo=r.costo();
        double demanda = r.demanda();
        
        assert(costo==instance.getDistanceMatrix()[1][2]);
        cout<<"Costo un nodo ✓"<<endl;

        assert(demanda == instance.getDemands()[2]);
        cout<<"Demanda un nodo ✓"<<endl;

        assert(r.ruta().size() == 1 );
        cout<<"Un nodo ✓"<<endl;

        assert(r.ruta()[0] == 2);
        cout<<"Es el único nodo ✓"<<endl;
    }

    //Agregar varios nodos
    {
        Ruta r(instance);
        r.agregarNodo(2,instance);
        r.agregarNodo(5,instance);
        r.agregarNodo(11,instance);
        double costo =r.costo();
        double demanda = r.demanda();

        assert(costo == (instance.getDistanceMatrix()[1][2]+instance.getDistanceMatrix()[2][5]+instance.getDistanceMatrix()[5][11]));
        cout<<"Costo varios nodos ✓"<<endl;

        assert(demanda == (instance.getDemands()[2]+instance.getDemands()[5]+instance.getDemands()[11]));
        cout<<"Demanda varias nodos ✓"<<endl;

        assert(r.ruta().size() == 3 );
        cout<<"Varios nodos ✓"<<endl;

        assert(r.ruta()[0]==2 && r.ruta()[1]==5 && r.ruta()[2]==11);
        cout<<"Están los nodos ✓"<<endl;
    }

    //Adyacencia al deposito: se trabaja bajo el supuesto de que la ruta ya está cerrada para esta función que solo se usa en Clarke and Wright
    {
        Ruta r(instance);
        r.agregarNodo(1,instance);
        r.agregarNodo(2,instance);
        r.agregarNodo(3,instance);
        r.agregarNodo(4,instance);
        r.agregarNodo(1,instance);

        assert(r.ruta()[0]==instance.getDepotId());
        assert(r.ruta()[4]==instance.getDepotId());
        cout<<"Ruta cerrada ✓"<<endl;

        assert(r.es_adyacente_a_d(2)==true);
        assert(r.es_adyacente_a_d(3)==false);
        assert(r.es_adyacente_a_d(4)==true);
        cout<<"Adyacencia verificada ✓"<<endl;
    }

    //Invertir ruta: se trabaja bajo el supuesto de que la ruta ya está cerrada para esta función que solo se usa en Clarke and Wright
    {
        Ruta r(instance);
        r.agregarNodo(1,instance);
        r.agregarNodo(2,instance);
        r.agregarNodo(3,instance);
        r.agregarNodo(4,instance);
        r.agregarNodo(1,instance);
        
        r.invertir_ruta();
        assert(r.demanda() == (instance.getDemands()[2]+instance.getDemands()[3]+instance.getDemands()[4])); //ver que la demanda no cambia
        assert(r.costo() == (instance.getDistanceMatrix()[1][2]+instance.getDistanceMatrix()[2][3]+instance.getDistanceMatrix()[3][4]+instance.getDistanceMatrix()[4][1]));

        assert(r.ruta()[1]==4 && r.ruta()[2]==3 && r.ruta()[3]==2);
        cout<<"Invertir funciona ✓"<<endl;
    }

    //Fusionar ruta: se trabaja bajo el supuesto de que las rutas ya están cerradas para esta función que solo se usa en Clarke and Wright
    {
        Ruta r1(instance); r1.agregarNodo(1,instance);r1.agregarNodo(2,instance); r1.agregarNodo(3,instance);r1.agregarNodo(1,instance);
        Ruta r2(instance); r2.agregarNodo(1,instance);r2.agregarNodo(4,instance); r2.agregarNodo(5,instance);r2.agregarNodo(1,instance);
        double costo_pre = r1.costo();
        r1.fusionar(r2,5.0); //Pasamos algun ahorro arbitrario

        assert(r1.ruta().size()==6);
        assert(r1.demanda()==((instance.getDemands()[2]+instance.getDemands()[3]+instance.getDemands()[4]+instance.getDemands()[5])));
        assert(r1.costo() == (costo_pre+r2.costo()-5.0));
        cout<<"Fusionar ✓"<<endl;
    }

    //Intercambiar
    {
        Ruta r1(instance); r1.agregarNodo(1,instance);r1.agregarNodo(2,instance); r1.agregarNodo(3,instance);r1.agregarNodo(1,instance);
        Ruta r2(instance); r2.agregarNodo(1,instance);r2.agregarNodo(4,instance); r2.agregarNodo(5,instance);r2.agregarNodo(1,instance);

        r1.intercambiar(r2,1,1,instance);

        assert(r1.ruta().size()==4 && r2.ruta().size()==4);
        assert(r1.ruta()[1]==4 && r2.ruta()[1]==2);

        assert(r1.costo()==(instance.getDistanceMatrix()[1][4]+instance.getDistanceMatrix()[4][3]+instance.getDistanceMatrix()[3][1]));
        assert(r2.costo()==(instance.getDistanceMatrix()[1][2]+instance.getDistanceMatrix()[2][5]+instance.getDistanceMatrix()[5][1]));

        assert(r1.demanda()==((instance.getDemands()[4]+instance.getDemands()[3]))); 
        assert(r2.demanda()==((instance.getDemands()[2]+instance.getDemands()[5])));
         
        cout<<"Intercambiar ✓"<<endl;
    }

    //Insertar
    {
        Ruta r1(instance); r1.agregarNodo(1,instance);r1.agregarNodo(2,instance); r1.agregarNodo(3,instance);r1.agregarNodo(1,instance);
        Ruta r2(instance); r2.agregarNodo(1,instance);r2.agregarNodo(4,instance); r2.agregarNodo(5,instance);r2.agregarNodo(1,instance);

        r1.insertar(r2,1,2,instance);

        assert(r1.ruta().size()==5 && r2.ruta().size()==3);
        assert(r1.ruta()[2]==4 && r1.ruta()[3]==3 && r2.ruta()[1]==5);

        assert(r1.costo()==(instance.getDistanceMatrix()[1][2]+instance.getDistanceMatrix()[2][4]+instance.getDistanceMatrix()[4][3]+instance.getDistanceMatrix()[3][1]));
        assert(r2.costo()==instance.getDistanceMatrix()[1][5]+instance.getDistanceMatrix()[5][1]);

        assert(r1.demanda()==((instance.getDemands()[2]+instance.getDemands()[4]+instance.getDemands()[3])));
        assert(r2.demanda() == (instance.getDemands()[5]));
        cout<<"Insertar ✓"<<endl;
    }
    return 0;
}