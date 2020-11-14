#include "../lists/Queue.h"
#include "../factory_structs/DeliveryCar.h"
#include "../factory_structs/Request.h"

struct WareHouse{
    DeliveryCar * car;
    Queue<Request *> * requests;

    // Constructor
    WareHouse(int carCapacity, int carDelay){
        car = new DeliveryCar(carCapacity, carDelay);
        requests = new Queue<Request *>();
    }

    // Funciones

    // Esta funcion agrega una peticion a la cola
    void makeRequest(Mixer * mixer, int amount){
        requests->enqueue(new Request(mixer, amount));
    }

    // Esta funcion va a permitir enviar una peticion a la maquina que lo solicito
    void sendRequest(){
        car->deliver(requests->dequeue());
    }
};
