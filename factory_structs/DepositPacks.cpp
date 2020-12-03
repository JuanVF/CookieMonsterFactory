#include <factory_structs/CookiePack.h>

struct DepositPacks{
    string nombre;

    int tiempo;
    int actual;
    int galletasPorPaquete;

    int paquetesActuales;
    int totalPaquetes;

    DepositPacks(string _nombre, int _galletasTotal, int _tiempo, int tp){
        nombre = _nombre;
        galletasPorPaquete = _galletasTotal;
        actual = 0;
        tiempo = _tiempo;
        totalPaquetes = tp;
        paquetesActuales = 0;
    }

    void agregarGalletas(int num){
        if (!isFinished() and ((num+actual)/galletasPorPaquete)<=totalPaquetes){
            actual +=num;
            paquetesActuales = actual/galletasPorPaquete;
        }
    }

    bool isFinished(){
        if (paquetesActuales == totalPaquetes){
            return true;
        }
        return false;
    }
};
