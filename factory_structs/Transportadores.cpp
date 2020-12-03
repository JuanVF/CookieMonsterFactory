#include <lists/LinkedList.h>
#include <factory_structs/Transportador.h>

struct Transportadores{
	int amount;
    string name;
	LinkedList<Transportador*>* transportadores;

    Transportadores(int cant){
        transportadores = new LinkedList<Transportador*>();
        amount = cant;
        name = "";
    }
	
    Transportadores(int cant, string _name){
        transportadores = new LinkedList<Transportador*>();
		amount = cant;	
        name = _name;
	}
	
};
