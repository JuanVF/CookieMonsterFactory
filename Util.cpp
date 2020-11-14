#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif

// Aqui se van a poner funciones generales
struct Util{

    // Constructor
    Util(){}

    // Funciones

    // Esta funcion pone a dormir el programa x segundos
    void delay(int seconds){
        clock_t start_time = clock();
        int end_time = start_time + (seconds * 1000);

        while(clock() < end_time);
    }
};
