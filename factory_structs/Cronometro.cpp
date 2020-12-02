#include <stdlib.h>
#include <windows.h>

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
            Sleep(1000);
        }
        segundos = 0 ;
    }


};
