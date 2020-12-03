#include <lists/LinkedList.h>
#include <lists/Queue.h>
#include <factory_structs/factoryStructs.h>
#include <machines/machines.h>
#include <factory_structs/Request.h>
#include <enums.h>

// Constructor
MixerMachine::MixerMachine(WareHouse * _warehouse, Assembler * _assembler, MixerType _type, string _name){
    delay = 0;
    min = 0;
    max = 0;
    amount = 0;
    name = _name;
    capacity = 0;

    isRunning = false;
    started = clock();

    type = _type;
    warehouse = _warehouse;
    assembler = _assembler;

    requests = new Queue<Request *>();
    processed = new LinkedList<Request *>();
}

// Funciones
void MixerMachine::setData(int _min, int _max, int _capacity, double _delay){
    min = _min;
    max = _max;
    capacity = _capacity;
    delay = _delay;
}

// Esta es la funcion que se va encargar de mezclar
void MixerMachine::mix(){
    if (!isRunning) return;

    bool canStart = (started + delay * 1000 - clock()) < 0;

    // Al principio va a hacer el primer pedido
    // Y va a esperar que llegue
    if (!needsIngredient() && canStart){
        started = clock();
        amount -= capacity;

        cout << name << " esta mezclando..." << endl;
        send(capacity);
    }else if (requests->isEmpty() && needsIngredient()){
        makeRequest();
    }
}

// Resetea los datos de las mezcladoras
void MixerMachine::reset(){
    while(requests->dequeue() != NULL);
    while(processed->removeFirst() != NULL);

}

// Esta funcion envia datos a la ensambladora
void MixerMachine::send(int amount){
    bool wasSended = assembler->receive(type, amount);

    // Si la banda transportadora se llena la maquina se apaga
    if (!wasSended){
        isRunning = false;
    }
}

// Esta funcion recibe la solicitud que le hizo al almacen
void MixerMachine::receive(int received){
    amount += received;
    cout << name << " ha recibido " << received << endl;

    // Se limita por si se llega al maximo
    if (amount > max) amount = max;

    processed->add(requests->dequeue());
}

// Esta funcion hace una peticion al almacen
void MixerMachine::makeRequest(){
    int toRequest = max - amount;

    if (toRequest == 0) return;

    cout << name << " ha hecho un pedido de " << toRequest << endl;

    Request * req = warehouse->makeRequest(this, toRequest);

    requests->enqueue(req);
}

// Retorna true si necesita ingrediente
bool MixerMachine::needsIngredient(){
    return amount - capacity <= 0;
}

// Retorna info necesaria para la UI
string MixerMachine::requestsPendingInfo(){
    string data = "";
    Node<Request *> * temp = requests->tail;

    if (temp == NULL) return data;

    for (int i = 0; i < requests->length; i++){
        data += temp->data->toString();
        temp = temp->next;
    }

    return data;
}

// Retorna info necesaria para la UI
string MixerMachine::requestsProcessedInfo(){
    string data = "";
    Node<Request *> * temp = processed->firstNode;

    if (temp == NULL) return data;

    for (int i = 0; i < processed->length; i++){
        data += temp->data->toString();
        temp = temp->next;
    }

    return data;
}
