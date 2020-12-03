#include <stdlib.h>
#include <windows.h>

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
            Sleep(1000);
        }
        segundos = 0 ;
    }

};
