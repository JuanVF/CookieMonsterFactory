#include <factory_structs/Request.h>
#include <Util.h>

struct DeliveryCar{
	int amountChocolate;
	int amountDough;
	int capacity;
	double delay;

    Util * utils;
	
	// Constructor
    // Delay en segundos
	DeliveryCar(int _capacity, double _delay){
		capacity = _capacity;
        delay = _delay;
		amountChocolate = 0;
		amountDough = 0;

        utils = new Util();
	}

    // Funciones

    // Esta funcion le envia el pedido a la maquina mezcladora
    void deliver(Request * request){
        utils->delay(delay);

        // Implementar algo para acceder a las maquinas
    }
};
