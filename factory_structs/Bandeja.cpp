#include <factory_structs/factoryStructs.h>
#include <factory_structs/Cronometro.h>
#ifndef IOSSTREAM
#define IOSSTREAM
#include <iostream>
using namespace std;
#endif

struct Bandeja{
    int capacity;
    int quantity;
    bool state;
    Cronometro * cronometro;

    Bandeja(){
        capacity = 50;
        quantity = 0;
        state = false;
    }
    Bandeja (int _c, int _q){
        capacity = _c;
        quantity = _q;
        cronometro = new Cronometro(10);
        state = false;
    }

    //modificar tiempo de la bandeja
    void modifyTime(double _time){
        cronometro->limite = _time;
    }

    //Modificar capacidad
    void modifyCapacity(int num){
        capacity  = num ;
    }

    //Agregar galletas a la bandeja
    void agregarGalletas(int num){
        if ((quantity+num)<=capacity and state){
            quantity += num ;
        }
        else if (state){
            quantity = capacity;
        }
    }

    //Encender
    void turnOn(){
        state = true ;
    }

    //Apagar
    void turnOff(){
        state = false;
    }

    //retorna el int de galletas que superan su capacidad
    int sobrantes(int num){
        int total = num+quantity;
        if (total>capacity){
            return total-capacity;
        }
        else{
            return 0;
        }
    }

    //retorna un bool en el caso de que si hayan sobrado galletas
    bool sobraron(int num){
        if ((num+quantity)>capacity){
            return true;
        }
        else
            return false;
    }

    //Limpia la bandeja
    void vaciarBandeja(){
        quantity = 0;
    }

};

