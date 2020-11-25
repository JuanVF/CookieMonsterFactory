#ifndef IOSSTREAM
#define IOSSTREAM
#include <iostream>
using namespace std;
#endif

// Esto de momento solo se usa para guardar la receta
struct Cookie{
	int amountDough;
	int amountChocolate;
	string measure;
	
    Cookie(){
		measure = "gramos";
        amountDough = 0;
        amountChocolate = 0;
	}	
};
