#include "VMC.h"
#include "CAW.h"
#include "swap.h"
#include "relocate.h"
#include "GRASP.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iomanip> 
using namespace std;
using namespace std::chrono;

vector<string> instancias = {
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E016-03m.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E016-05m.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E021-04m.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E021-06m.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E022-04g.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E022-06m.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E023-03g.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E023-05S.DAT",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E026-08m.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E030-03g.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E030-04S.DAT",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E031-09h.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E033-03N.DAT",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E033-04g.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E033-05s.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E036-11h.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E041-14h.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E045-04f.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E048-04y.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E051-05e.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E072-04f.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E076-07s.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E076-07u.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E076-08s.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E076-08u.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E076-10e.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E076-14s.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E076-14u.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E076-15s.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E076A10r.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E076B09r.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E076C09r.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E076D09r.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E101-08e.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E101-10c.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E101-14s.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E101-14u.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E101A11r.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E101B11r.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E101C11r.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E101D11r.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E121-07c.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E135-07f.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E151-12b.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E151-12c.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E151A15r.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E151B14r.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E151C14r.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E151D14r.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E200-16b.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E200-16c.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E200-17b.dat",
    "/workspaces/TP2-TD5/tp2/instancias/2l-cvrp-0/E200-17c.dat",
};


int main(){
    ofstream header("resultados_grasprelocate.csv", ios::trunc);
    
    header << "Instancia;Grasp 10;Grasp 100;Grasp 1000; Grasp 10000\n";
    header.close();

    for(int i=0;i<instancias.size();i++){
    try {
            ofstream out("resultados_grasprelocate.csv", ios::app);
            out << fixed << setprecision(3);
            VRPLIBReader instance(instancias[i]);

            //GRASP
            GRASP grasp10;
            Solucion sgrasp10=grasp10.resolver(4,10,instance);
            for(int i=0;i<100;i++){
                relocate(sgrasp10,instance);
            }
            double costog10=sgrasp10.costo();

            GRASP grasp100;
            Solucion sgrasp100=grasp100.resolver(4,100,instance);
            for(int i=0;i<100;i++){
                relocate(sgrasp100,instance);
            }
            double costog100=sgrasp100.costo();

            GRASP grasp1000;
            Solucion sgrasp1000=grasp1000.resolver(4,1000,instance);
            for(int i=0;i<100;i++){
                relocate(sgrasp1000,instance);
            }
            double costog1000=sgrasp1000.costo();

            GRASP grasp10000;
            Solucion sgrasp10000=grasp10000.resolver(4,10000,instance);
            for(int i=0;i<100;i++){
                relocate(sgrasp10000,instance);
            }
            double costog10000=sgrasp10000.costo();

            string instancia="";
            int j=45;
            while(instancias[i][j]!='.'){
                instancia.push_back(instancias[i][j]);
                j++;
            }

            out<<instancia<<";"<<costog10<<";"<<costog100<<";"<<costog1000<<";"<<costog10000<<";"<<"\n";

            out.close();

            cout << "Terminó: " << instancias[i] << endl;

        } catch (exception& e) {
            cerr << "Error con instancia: " << instancias[i] << " → " << e.what() << endl;
        }
    }
    
    return 0;
}