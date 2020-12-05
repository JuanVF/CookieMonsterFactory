#include <machines/machines.h>
#include <lists/Queue.h>
#include <factory_structs/DeliveryCar.h>
#include <factory_structs/Request.h>
#include <Util.h>

// Constructor
WareHouse::WareHouse(){
    car = new DeliveryCar();
    requests = new Queue<Request*>();
    hasChanged = false;
}

// Permite a la UI settear los datos
void WareHouse::setData(double _delay, int _capacity){
    car->delay = _delay;
    car->capacity = _capacity;
}

bool WareHouse::canStart(){
    bool can = car->capacity != 0 && car->delay != 0;

    return can;
}

// Resetea los datos de las maquinas
void WareHouse::reset(){
    // Se vacia la lista
    while(requests->dequeue() != NULL);
}

// Permite al mixer machine hacer pedidos
Request * WareHouse::makeRequest(MixerMachine * mixer, int amount){
    cout << "Se ha solicitado: " << amount << " por parte de " << mixer->name << endl;
    Request * req = new Request(mixer, amount);

    requests->enqueue(req);

    return req;
}

// Esto le brinda a la UI un string con la info de los strings
string WareHouse::requestsInfo(){
    string data = "";
    Node<Request *> * temp = requests->tail;

    if (temp == NULL) return "";

    for (int i = 0; i < requests->length; i++){
        if (temp == NULL) break;

        data += temp->data->toString();
        temp = temp->next;
    }

    return data;
}

// Envia los pedidos a la maquina mezcladora
void WareHouse::sendRequest(){
    bool wasSend = car->deliver(requests->peek());

    if (wasSend){
        cout << "El carrito envio un request!" << endl;
        requests->dequeue();
    }
}

// Esta es la funcion que se esta ejecutando para estar verificando
// Los pedidos
void WareHouse::checking(){
    if (!isRunning) return;

    if (!requests->isEmpty()){
        sendRequest();
    }
}
