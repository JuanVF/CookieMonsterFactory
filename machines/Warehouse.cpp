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

// Permite al mixer machine hacer pedidos
Request * WareHouse::makeRequest(MixerMachine * mixer, int amount){
    cout << "Se ha solicitado: " << amount << " por parte de " << mixer->name << endl;
    Request * req = new Request(mixer, amount);
    isRunning = false;

    requests->enqueue(req);

    return req;
}

// Esto le brinda a la UI un string con la info de los strings
string WareHouse::requestsInfo(){
    string data = "";
    Node<Request *> * temp;

    for (int i = 0; i < requests->length; i++){
        temp = requests->tail;

        data += temp->data->toString();
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
    if (!requests->isEmpty()){
        sendRequest();
    }
}
