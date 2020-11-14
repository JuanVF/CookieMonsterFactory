#include <lists/LinkedList.h>
#include <factory_structs/Transportador.h>

struct Transportadores{
	int amount;
	LinkedList<Transportador*>* transportadores;
	
	Transportadores(int cant){
        transportadores = new LinkedList<Transportador*>();
		amount = cant;	
	}
	
};
