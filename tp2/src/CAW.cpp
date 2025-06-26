#include "CAW.h"

CAW::CAW(){}

Solucion CAW::resolver(const VRPLIBReader & instance ){
    int depot = instance.getDepotId();

    //Aqui se hacen todas las rutas deposito->cliente->deposito
    for (auto i:instance.getNodes()) {
        if (i.id != depot){
            Ruta r(instance);
            r.agregarNodo(depot, instance); 
            r.agregarNodo(i.id, instance);                     
            r.agregarNodo(depot, instance); 
            rutas_iniciales.push_back(r);
        }
    }

    //Calculamos el ahorro con la formula de Clarke & Wright: Ahorro(i,j)=d[depot][i]+d[depot][j]-d[i][j]
    for (auto i:instance.getNodes()) {
        for(auto j:instance.getNodes()){
            if(i.id!=depot && j.id!=depot && i.id<j.id) //No hacer duplicados
            _ahorros.push_back(instance.getDistanceMatrix()[i.id][depot]+instance.getDistanceMatrix()[j.id][depot]-instance.getDistanceMatrix()[i.id][j.id]);
            _par.push_back({i.id,j.id});
        }
    }

    //Ordenamos decrecientemente los ahorros, lo hacemos con selection sort para poder ordenar el vector de pares tambien
    for(int i = 0;i<_ahorros.size();i++){
        int max = _ahorros[i];
        int pos = i;
        for(int j = i+1;j<_ahorros.size();j++){
            if(_ahorros[j]>max){
                max = _ahorros[j];
                pos = j;
            }
        }
        swap(_ahorros[i],_ahorros[pos]);
        swap(_par[i],_par[pos]);
    }

}
