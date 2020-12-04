#include <factory_structs/CookiePack.h>

struct DepositPacks{
    string nombre;

    int tiempo;
    int actual;
    int galletasPorPaquete;

    int paquetesActuales;
    int totalPaquetes;

    int probabilidad;

    DepositPacks(string _nombre, int _galletasTotal, int _tiempo, int tp){
        nombre = _nombre;
        galletasPorPaquete = _galletasTotal;
        actual = 0;
        tiempo = _tiempo;
        totalPaquetes = tp;
        paquetesActuales = 0;
        probabilidad = 0;
    }

    void agregarGalletas(int num){
        while (!isFinished()){
            if ((actual+num)>=galletasPorPaquete){
                actual += num;
                totalPaquetes +=actual/galletasPorPaquete;
                while(actual>=galletasPorPaquete){
                    actual-= galletasPorPaquete;
                }
            }
            else{
                actual +=num;
            }
        }
    }

    bool isFinished(){
        if (paquetesActuales == totalPaquetes){
            return true;
        }
        return false;
    }
};
