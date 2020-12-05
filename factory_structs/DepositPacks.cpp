#include <factory_structs/factoryStructs.h>

#ifndef IOSSTREAM
#define IOSSTREAM
#include <iostream>
using namespace std;
#endif

DepositPacks::DepositPacks(string _nombre, int _galletasTotal, int _tiempo, int tp){
    nombre = _nombre;
    tiempo = _tiempo;

    galletasPorPaquete = _galletasTotal;
    actual = 0;

    totalPaquetes = tp;
    paquetesActuales = 0;

    probabilidad =0;
    paquetesEntregados =0;
    cronometro = new Cronometro(_tiempo);
}

void DepositPacks::agregarGalletas(int num){
    if(!isFinished()){
        actual +=num;

         if (actual >= galletasPorPaquete){
            actual -= galletasPorPaquete;
            totalPaquetes ++;
        }
    }

    /*while (!isFinished()){
        if ((actual + num) >= galletasPorPaquete){
            actual += num;
            totalPaquetes += actual/galletasPorPaquete;

            while(actual > galletasPorPaquete){
                actual -= galletasPorPaquete;
            }
        }
        else{
            actual += num;
        }
    }*/
}

void DepositPacks::entregarPacks(){
    paquetesEntregados +=1;
}

bool DepositPacks::entregaTerminada(){
    if (totalPaquetes == paquetesEntregados){
        return true;
    }
    return false;
}

bool DepositPacks::isFinished(){
    if (paquetesActuales >= totalPaquetes){
        if (paquetesActuales > totalPaquetes) paquetesActuales = totalPaquetes;

        return true;
    }

    return false;
}
