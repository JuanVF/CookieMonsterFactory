#include <stdlib.h>
#include <Util.h>

using namespace std;

#include <factory_structs/factoryStructs.h>

Cronometro::Cronometro(double _limit){
    segundos = 0;
    limite = _limit;
}

bool Cronometro::contadorB(){
    while (1){
        segundos++;
        if (segundos ==limite){
            return true;
        }
        (new Util())->delay(1);
    }
    segundos = 0 ;
}
