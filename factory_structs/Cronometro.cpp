#include <stdlib.h>
#include <Util.h>

using namespace std;

struct Cronometro{
    int segundos = 0;
    double limite;

    Cronometro(double _limit){
        segundos = 0;
        limite = _limit;
    }

    bool contadorB(){
        while (1){
            segundos++;
            if (segundos ==limite){
                return true;
            }
            (new Util())->delay(1);
        }
        segundos = 0 ;
    }
};
