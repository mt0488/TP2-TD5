#include "CAW.h"

CAW::CAW(){}

Solucion CAW::resolver(const VRPLIBReader & instance ){
    int depot = instance.getDepotId();
    int capacidad = instance.getCapacity();
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
            if(i.id!=depot && j.id!=depot && i.id<j.id){ //No hacer duplicados
            _ahorros.push_back(instance.getDistanceMatrix()[i.id][depot]+instance.getDistanceMatrix()[j.id][depot]-instance.getDistanceMatrix()[i.id][j.id]);
            _par.push_back({i.id,j.id});
        }
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
    
    for(int k = 0; k<_par.size();k++){
        int i = _par[k].first;
        int j = _par[k].second;
        
        int id_i = -1 , id_j = -1;

        //Buscamos las rutas donde esten i y j
        for(int s = 0;s<rutas_iniciales.size();s++){
            Ruta& r = rutas_iniciales[s];
            if(r.es_adyacente_a_d(i)) id_i = s;
            if(r.es_adyacente_a_d(j)) id_j = s;
        }

        //Vemos que se cumplan las condiciones para combinar las rutas donde estan i y j
        if(id_i!=-1 && id_j != -1 && id_i!=id_j){
            Ruta& ri = rutas_iniciales[id_i];
            Ruta& rj = rutas_iniciales[id_j];

            if(ri.demanda()+rj.demanda()<=capacidad){
                double dij = -_ahorros[k];
                
                if(ri.ruta()[1]==i && rj.ruta()[1] ==j){
                    rj.invertir_ruta();
                    rj.fusionar(ri,dij);
                    rutas_iniciales.erase(rutas_iniciales.begin() + id_i);
                }else if(ri.ruta()[1]!=i && rj.ruta()[1] ==j){
                    ri.fusionar(rj,dij);
                    rutas_iniciales.erase(rutas_iniciales.begin() + id_j);
                }else if(ri.ruta()[1]!=i && rj.ruta()[1] !=j){
                    rj.invertir_ruta();
                    ri.fusionar(rj,dij);
                    rutas_iniciales.erase(rutas_iniciales.begin() + id_j);
                }else if(ri.ruta()[1]==i && rj.ruta()[1] !=j){
                    ri.invertir_ruta();
                    rj.fusionar(ri,dij);
                    rutas_iniciales.erase(rutas_iniciales.begin() + id_i);
                }
            }
        }
    }

    Solucion sol;
    for (Ruta& r : rutas_iniciales) {
        sol.añadirRuta(r);
    }
    return sol;
}

