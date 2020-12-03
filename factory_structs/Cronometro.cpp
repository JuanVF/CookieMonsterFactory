#include <stdlib.h>
#include <Util.h>

using namespace std;

struct Cronometro{
    int segundos =0;

    Cronometro(){
        segundos = 0;
    }

    bool contadorB(int limite){
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
