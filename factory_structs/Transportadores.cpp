
#include "../lists/LinkedList.h"


struct Transportadores{
	int amount;
	LinkedList<Transportador*>* transportadores;
	
	Transportadores(int cant){
		transportadores = new CircularList<Transportador*>();
		amount = cant;	
	}
	
};
