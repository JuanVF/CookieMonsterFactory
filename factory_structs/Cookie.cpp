#include <factory_structs/factoryStructs.h>

#ifndef IOSSTREAM
#define IOSSTREAM
#include <iostream>
using namespace std;
#endif

Cookie::Cookie(){
    measure = "gramos";
    amountDough = 0;
    amountChocolate = 0;
}

void Cookie::setData(double _amountDough, double _amountChocolate){
    amountDough = _amountDough;
    amountChocolate = _amountChocolate;
}
