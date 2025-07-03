#ifndef SWAP_H
#define SWAP_H

#include "Solucion.h"
#include "VRPLIBReader.h"

bool esSwapFactible(const Ruta& r1, const Ruta& r2, int idx1, int idx2, const VRPLIBReader& instance);
void swapRutas(Solucion& s, const VRPLIBReader& instance);

#endif
