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
	
	Cookie(int dough, int chocolate){
		measure = "gramos";
		amountDough = dough;
		amountChocolate = chocolate;
	}	
};
