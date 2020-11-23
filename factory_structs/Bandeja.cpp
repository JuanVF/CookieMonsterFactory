#ifndef IOSSTREAM
#define IOSSTREAM
#include <iostream>
using namespace std;
#endif

struct Bandeja{
    int capacity;
    int quantity;

    Bandeja(){
        capacity = 50;
        quantity = 0;
    }
    Bandeja (int _c, int _q){
        capacity = _c;
        quantity = _q;
    }

    void aumentarCantidad(int num){
        quantity = num;
    }
};

