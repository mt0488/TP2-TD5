#include "relocate.h"
using namespace std;

void relocate(Solucion & s,const VRPLIBReader & instance){
    double min=0.0;
    int i1, i2, ruta1, ruta2;

    vector<Ruta>& rutas=s.rutas();

    for(int i = 0; i<rutas.size();i++){
        for(int j=0;j<rutas.size();j++){
            if(i!=j){
                const Ruta& r1=rutas[i];
                const Ruta& r2=rutas[j];
                for(int id_1=1;id_1<(r1.ruta()).size()-1;id_1++){
                    if(r2.demanda()+instance.getDemands()[r1.ruta()[id_1]]<=instance.getCapacity()){ //Es un relocate factible
                        for(int id_2=1;id_2<(r2.ruta()).size()-1;id_2++){
                            
                            double ar1 = instance.getDistanceMatrix()[r1.ruta()[id_1]][r1.ruta()[id_1-1]]; //Arista del anterior al nodo actual en ruta 1
                            double ar2 = instance.getDistanceMatrix()[r1.ruta()[id_1]][r1.ruta()[id_1+1]]; //Arista del siguiente al nodo actual en ruta 1
                            double ar3=instance.getDistanceMatrix()[r2.ruta()[id_2]][r2.ruta()[id_2-1]]; //Arista del anterior al nodo actual en ruta 2

                            double ar4 = instance.getDistanceMatrix()[r1.ruta()[id_1-1]][r1.ruta()[id_1+1]]; //Arista entre el anterior y el siguiente al nodo actual en ruta 1
                            double ar5 = instance.getDistanceMatrix()[r2.ruta()[id_2-1]][r1.ruta()[id_1]]; //Arista entre el anterior al nodo actual en ruta 2 y el nodo actual en ruta 1
                            double ar6 = instance.getDistanceMatrix()[r1.ruta()[id_1]][r2.ruta()[id_2]]; //Arista entre los dos nodos

                            double costo_actual=ar1+ar2+ar3;
                            double costo_nuevo=ar4+ar5+ar6;
                            double diferencia=costo_actual-costo_nuevo;
                            if(diferencia>min){ //Estrategia Best improvement
                                i1=id_1;
                                i2=id_2;
                                ruta1=i;
                                ruta2=j;
                                min=diferencia;
                            }

                        }
                    }
                }
            }
        }
    }
    if(min>0.0){
        rutas[ruta2].insertar(rutas[ruta1],i1,i2,instance);
        s.recalcularCosto();
    }    
}