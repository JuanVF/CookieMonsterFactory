#include <regex>
#include <string>

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif

#ifndef IOSSTREAM
#define IOSSTREAM
#include <iostream>
using namespace std;
#endif

// Aqui se van a poner funciones generales
struct Util{

    // Constructor
    Util(){}

    // Funciones

    // Esta funcion pone a dormir el programa x segundos
    void delay(double seconds){
        clock_t start_time = clock();
        double end_time = start_time + (seconds * 1000);

        while(clock() < end_time);
    }

    // Parsea un string a solo numeros
    string onlyNumbers(string str){
        regex str_exp("\\d+(\\.)?(\\d{1,5})?");
        smatch results;

        regex_search(str, results, str_exp);

        return results[0];
    }

    // Convierte un string a double
    double toDouble(string str){
        return stod(str);
    }

    // Convierte un string a int
    int toInt(string str){
        return stoi(str);
    }
};
