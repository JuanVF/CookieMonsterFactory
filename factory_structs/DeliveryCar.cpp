#include <factory_structs/Request.h>
#include <machines/machines.h>

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif


struct DeliveryCar{
	int capacity;
    double delay;
    clock_t started;
	
	// Constructor
    // Delay en segundos
    DeliveryCar(){
        capacity = 0;
        delay = 0;

        started = clock();
	}

    // Funciones

    // Esta funcion le envia el pedido a la maquina mezcladora
    bool deliver(Request * request){
        bool canSend = (started + delay*1000 - clock()) <= 0;

        // Esto es para el delay
        if (!canSend) return false;
        started = clock();

        int amount = request->amount;

        if (amount >= capacity){
            amount = capacity;
            request->amount -= capacity;
        }

        request->mixer->receive(amount);

        return amount < capacity;
    }
};
