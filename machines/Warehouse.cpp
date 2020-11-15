#include <machines/machines.h>
#include <lists/Queue.h>
#include <factory_structs/DeliveryCar.h>
#include <factory_structs/Request.h>

// NOTA: La MixerMachine tiene que ser importada solo su prototipo...
//       Si se importa como tal va a dar muchos errores de definicion
//       no lo modifique si lo va a hacer
struct WareHouse{
    DeliveryCar * car;
    Queue<Request*> * requests;

    // Constructor
    WareHouse(int carCapacity, int carDelay){
        car = new DeliveryCar(carCapacity, carDelay);
        requests = new Queue<Request*>();
    }

    // Funciones

    // Esta funcion agrega una peticion a la cola
    Request * makeRequest(MixerMachine * mixer, int amount){
        Request * req = new Request(mixer, amount);

        requests->enqueue(req);

        return req;
    }

    // Esta funcion va a permitir enviar una peticion a la maquina que lo solicito
    void sendRequest(){
        car->deliver(requests->dequeue());
    }
};
