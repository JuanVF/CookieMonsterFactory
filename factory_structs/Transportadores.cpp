#include "../lists/LinkedList.h"
#include "Transportador.h"

struct Transportadores{
	int amount;
	LinkedList<Transportador*>* transportadores;
	
	Transportadores(int cant){
        transportadores = new LinkedList<Transportador*>();
		amount = cant;	
	}
	
};
