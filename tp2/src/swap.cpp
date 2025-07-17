#include "swap.h"

using namespace std;

//Ver que el intercambio no afecta las capacidades
bool esSwapFactible(const Ruta& r1, const Ruta& r2, int idx1, int idx2, const VRPLIBReader& instance) {
    int capacidad = instance.getCapacity();

    int demanda_cliente1 = instance.getDemands()[r1.ruta()[idx1]];
    int demanda_cliente2 = instance.getDemands()[r2.ruta()[idx2]];

    int nueva_demanda_r1 = r1.demanda() - demanda_cliente1 + demanda_cliente2;
    int nueva_demanda_r2 = r2.demanda() - demanda_cliente2 + demanda_cliente1;

    return nueva_demanda_r1 <= capacidad && nueva_demanda_r2 <= capacidad;
}

void swapRutas(Solucion & s,const VRPLIBReader & instance){
    Solucion s0=s;
    int id1;
    int id2;
    int ruta1; int ruta2;
    double min=0.0;
    vector<Ruta>& r = s.rutas();

    for(int i=0;i<r.size();i++){
        for(int j = i+1;j<r.size();j++){
            const Ruta& r1=r[i];
            const Ruta& r2=r[j];

            for(int id_1=1;id_1<(r1.ruta()).size()-1;id_1++){
                for(int id_2=1;id_2<(r2.ruta()).size()-1;id_2++){
                
                    if(esSwapFactible(r1,r2,id_1,id_2,instance)){
                        double ar1=instance.getDistanceMatrix()[r1.ruta()[id_1]][r1.ruta()[id_1-1]]; //Arista del anterior al nodo actual en ruta 1
                        double ar2=instance.getDistanceMatrix()[r1.ruta()[id_1]][r1.ruta()[id_1+1]]; //Arista del siguiente al nodo actual en ruta 1
                        double ar3=instance.getDistanceMatrix()[r2.ruta()[id_2]][r2.ruta()[id_2-1]]; //Arista del anterior al nodo actual en ruta 2
                        double ar4=instance.getDistanceMatrix()[r2.ruta()[id_2]][r2.ruta()[id_2+1]]; //Arista del anterior al nodo actual en ruta 2

                        double ar5=instance.getDistanceMatrix()[r1.ruta()[id_1]][r2.ruta()[id_2-1]]; //Nueva arista entre el anterior al nodo actual en ruta 2 y el actual en ruta 1
                        double ar6=instance.getDistanceMatrix()[r1.ruta()[id_1]][r2.ruta()[id_2+1]]; //Nueva arista entre el siguiente al nodo actual en ruta 2 y el actual en ruta 1
                        double ar7=instance.getDistanceMatrix()[r2.ruta()[id_2]][r1.ruta()[id_1-1]]; //Nueva arista entre el anterior al nodo actual en ruta 1 y el actual en ruta 2
                        double ar8=instance.getDistanceMatrix()[r2.ruta()[id_2]][r1.ruta()[id_1+1]]; //Nueva arista entre el siguiente al nodo actual en ruta 1 y el actual en ruta 2

                        double costo_actual=ar1+ar2+ar3+ar4;
                        double costo_nuevo=ar5+ar6+ar7+ar8;
                        double diferencia=costo_actual-costo_nuevo;
                        if(diferencia>min){ //Estrategia Best improvement
                            id1=id_1;
                            id2=id_2;
                            ruta1=i;
                            ruta2=j;
                            min=diferencia;
                        }
                    }
                
            }
            }
        }
    }
    if(min>0.0){
        r[ruta1].intercambiar(r[ruta2],id1,id2,instance);
        s.recalcularCosto();
    }
    if(s.costo()<s0.costo()){
        swapRutas(s,instance);
    }
}