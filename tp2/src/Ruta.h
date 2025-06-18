#ifndef RUTA_H
#define RUTA_H

#include <vector>
#include "VRPLIBReader.h"

class Ruta {
public:
    explicit Ruta(const VRPLIBReader& instance);

    void agregarNodo(int n, const VRPLIBReader& instance);

    int demanda() const;
    int costo() const;

    const std::vector<int>& ruta() const; //devolver los ids

private:
    std::vector<int> ids;  //Empieza y termina en el id del deposito.
    std::vector<int> demandas;
    int _costo; //El costo de la ruta solucion.
    int _demanda; //La suma de las demandas de los nodos en ids
};
 
#endif 
