#include <factory_structs/factoryStructs.h>

#ifndef IOSSTREAM
#define IOSSTREAM
#include <iostream>
using namespace std;
#endif

DepositPacks::DepositPacks(string _nombre, int _galletasTotal, int _tiempo, int tp){
    nombre = _nombre;
    galletasPorPaquete = _galletasTotal;
    actual = 0;
    tiempo = _tiempo;
    totalPaquetes = tp;
    paquetesActuales = 0;
}
void DepositPacks::agregarGalletas(int num){
    if (!isFinished() and ((num+actual)/galletasPorPaquete)<=totalPaquetes){
        actual +=num;
        paquetesActuales = actual/galletasPorPaquete;
    }
}

bool DepositPacks::isFinished(){
    if (paquetesActuales == totalPaquetes){
        return true;
    }
}

void DepositPacks::cambiarProbabilidad(int np){
    probabilidad = np;
}
