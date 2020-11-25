#include <lists/Queue.h>
#include <factory_structs/factoryStructs.h>
#include <machines/Warehouse.h>
#include <enums.h>

// Constructor
MixerMachine::MixerMachine(WareHouse * _warehouse, int _id, double _delay, int _min, int _max, MixerType _type){
    delay = _delay;
    min = _min;
    max = _max;
    type = _type;
    amount = 0;
    id = _id;
    isRunning = true;
    isStarting = true;

    warehouse = _warehouse;
    requests = new Queue<Request *>();
}

// Funciones

// Esta es la funcion que se va encargar de mezclar
void MixerMachine::mix(){
    // Al principio va a hacer el primer pedido
    // Y va a esperar que llegue
    if (needsIngredient()){
        makeRequest();
        while(requests->isEmpty());
    }

    // Ciclo de mezcla
    while(isRunning){
        if (!needsIngredient()){
            // Mezcle haga algo
            // Necesito a la ensambladora
        }else{
            makeRequest();
        }
    }
}

// Esta funcion recibe la solicitud que le hizo al almacen
void MixerMachine::receive(int received){
    amount += received;

    // Se limita por si se llega al maximo
    if (amount > max) amount = max;

    requests->dequeue();
}

// Esta funcion hace una peticion al almacen
void MixerMachine::makeRequest(){
    int toRequest = max - amount;

    Request * req = warehouse->makeRequest(this, toRequest);

    requests->enqueue(req);
}

// Retorna true si necesita ingrediente
bool MixerMachine::needsIngredient(){
    return amount < max;
}
