#include <factory_structs/Request.h>
#include <machines/machines.h>
#include <Util.h>

struct DeliveryCar{
	int capacity;
	double delay;

    Util * utils;
	
	// Constructor
    // Delay en segundos
    DeliveryCar(){
        capacity = 0;
        delay = 0;

        utils = new Util();
	}

    // Funciones

    // Esta funcion le envia el pedido a la maquina mezcladora
    void deliver(Request * request){
        utils->delay(delay);

        request->mixer->receive(request->amount);
    }
};
