#include <machines/machines.h>
#include <lists/Queue.h>
#include <factory_structs/DeliveryCar.h>
#include <factory_structs/Request.h>


// Constructor
WareHouse::WareHouse(){
    car = new DeliveryCar();
    requests = new Queue<Request*>();
}

// Permite al mixer machine hacer pedidos
Request * WareHouse::makeRequest(MixerMachine * mixer, int amount){
    Request * req = new Request(mixer, amount);
    isRunning = false;

    requests->enqueue(req);

    return req;
}

// Envia los pedidos a la maquina mezcladora
void WareHouse::sendRequest(){
    car->deliver(requests->dequeue());
}

// Esta es la funcion que se esta ejecutando para estar verificando
// Los pedidos
void WareHouse::checking(){
    while(isRunning){
        if (!requests->isEmpty()){
            sendRequest();
        }
    }
}
