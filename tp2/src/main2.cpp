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
    ofstream header("resultados_tiempos.csv", ios::trunc);
    
    header << "Instancia;Vecino más cercano;Clarke and Wright;Vecino más cercano + swap;Vecino más cercano + relocate;Clarke and Wright + swap;Clarke and Wright + relocate; Vecino más cercano + swap + relocate\n";
    header.close();

    for(int i=0;i<instancias.size();i++){
    try {
            ofstream out("resultados_tiempos.csv", ios::app);
            out << fixed << setprecision(3);
            VRPLIBReader instance(instancias[i]);

            //Vecino mas cercano
            VMC vmc;
            auto startVMC = high_resolution_clock::now();
            Solucion solVMC = vmc.resolver(instance);
            auto endVMC = high_resolution_clock::now();
            auto tiempoVMC = duration_cast<microseconds>(endVMC - startVMC);

            double costovmc = solVMC.costo();
           

            //out <<instancias[i] << ";Vecino más cercano;" << costovmc << ";" <<  tiempoVMC.count() << ";"  << "\n";

            //Clarke and Wright
            
            CAW caw;
            auto startcaw = high_resolution_clock::now();
            Solucion solcaw = caw.resolver(instance);
            auto endcaw = high_resolution_clock::now();
            auto tiempocaw = duration_cast<microseconds>(endcaw - startcaw);
            string relax="";
            double costocaw = solcaw.costo();
            if(solcaw.rutas().size()>instance.getNumVehicles()) relax = "Restricción relajada";
            //out << instancias[i] << ";Clarke and Wright;" << costocaw << ";" << tiempocaw.count() << ";" << relax<< "\n";

            //Vecino mas cercano + swap
            VMC vmcSwap;
            auto startvmcswap = high_resolution_clock::now();
            Solucion solvmcswap = vmcSwap.resolver(instance);
            swapRutas(solvmcswap,instance);
            auto endvmcswap = high_resolution_clock::now();
            auto tiempovmcswap = duration_cast<microseconds>(endvmcswap - startvmcswap);

            double costovmcSwap = solvmcswap.costo();

            //out << instancias[i] << ";Vecino mas cercano + swap;" << costovmcSwap << ";"  << tiempovmcswap.count() << ";" << "\n";

            //Vecino mas cercano + relocate
            VMC vmcrel;
            auto startvmcrel = high_resolution_clock::now();
            Solucion solvmcrel = vmcrel.resolver(instance);
            relocate(solvmcrel,instance);
            auto endvmcrel = high_resolution_clock::now();
            auto tiempovmcrel = duration_cast<microseconds>(endvmcrel - startvmcrel);

            double costovmcrel = solvmcrel.costo();

            //out << instancias[i] << ";Vecino mas cercano + relocate;" << costovmcrel << ";"  << tiempovmcrel.count() << ";" << "\n";

            //Clarke and Wright + swap
            CAW cawSwap;
            auto startcawswap = high_resolution_clock::now();
            Solucion solcawswap = cawSwap.resolver(instance);
            swapRutas(solcawswap,instance);
            auto endcawswap = high_resolution_clock::now();
            auto tiempocawswap = duration_cast<microseconds>(endcawswap - startcawswap);

            double costocawSwap = solcawswap.costo();
            relax="";
            if(solcawswap.rutas().size()>instance.getNumVehicles()) relax = "Restricción relajada";
            //out << instancias[i] << ";Clarke and wright + swap;" << costocawSwap << ";"  << tiempocawswap.count() << ";" << relax << "\n";

            //Clarke and Wright + relocate
            CAW cawrel;
            auto startcawrel = high_resolution_clock::now();
            Solucion solcawrel = cawrel.resolver(instance);
            relocate(solcawrel,instance);
            auto endcawrel = high_resolution_clock::now();
            auto tiempocawrel = duration_cast<microseconds>(endcawrel - startcawrel);

            double costocawrel = solcawrel.costo();
            relax="";
            if(solcawrel.rutas().size()>instance.getNumVehicles()) relax = "Restricción relajada";
           // out << instancias[i] << ";Clarke and wright + relocate;" << costocawrel << ";"  << tiempocawrel.count() << ";" << relax << "\n";

            //Vecino mas cercano + swap + relocate
            VMC vmcall;
            auto startvmcall = high_resolution_clock::now();
            Solucion solvmcall = vmcall.resolver(instance);
            swapRutas(solvmcall,instance);
            relocate(solvmcall,instance);
            auto endvmcall = high_resolution_clock::now();
            auto tiempovmcall = duration_cast<microseconds>(endvmcall - startvmcall);

            double costovmcall = solvmcall.costo();

            //out << instancias[i] << ";Vecino mas cercano + swap + relocate;" << costovmcall << ";"  << tiempovmcall.count() << ";" << "\n";

            string instancia="";
            int j=45;
            while(instancias[i][j]!='.'){
                instancia.push_back(instancias[i][j]);
                j++;
            }
            out<<instancia<<";"<<tiempoVMC.count()<<";"<<tiempocaw.count()<<";"<<tiempovmcswap.count()<<";"<<tiempovmcrel.count()<<";"<<tiempocawswap.count()<<";"<<tiempocawrel.count()<<";"<<tiempovmcall.count()<<"\n";

            out.close();

            cout << "Terminó: " << instancias[i] << endl;

        } catch (exception& e) {
            cerr << "Error con instancia: " << instancias[i] << " → " << e.what() << endl;
        }
    }
    
    return 0;
}