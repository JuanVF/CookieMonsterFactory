#include <stdlib.h>
#include <Util.h>

using namespace std;

#include <factory_structs/factoryStructs.h>

Cronometro::Cronometro(double _limit){
    segundos = 0;
    limite = _limit;
    time = clock();
}

bool Cronometro::contadorB(){
    if ((time + limite * 1000 - clock()) <= 0){
        time = clock();
        return true;
    }

    return false;

    /*while (1){
        segundos++;
        if (segundos ==limite){
            return true;
        }
        (new Util())->delay(1);
    }*/
};
