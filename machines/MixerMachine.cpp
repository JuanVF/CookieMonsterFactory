#include <lists/Queue.h>
#include <factory_structs/factoryStructs.h>
#include <machines/machines.h>
#include <enums.h>
#include <Util.h>

// Constructor
MixerMachine::MixerMachine(WareHouse * _warehouse, Assembler * _assembler, MixerType _type, string _name){
    delay = 0;
    min = 0;
    max = 0;
    amount = 0;
    name = _name;
    capacity = 0;

    isRunning = false;

    type = _type;
    warehouse = _warehouse;
    assembler = _assembler;

    requests = new Queue<Request *>();
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
    Util * util = new Util();

    // Al principio va a hacer el primer pedido
    // Y va a esperar que llegue
    if (isRunning && needsIngredient()){
        makeRequest();
    }

    while(isRunning){
        if (!needsIngredient()){
            amount -= capacity;

            cout << type << " esta cocinando..." << endl;
            send(capacity);
        }else{
            makeRequest();
        }

        util->delay(1/60);
    }
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
    return amount < max || amount - capacity < max;
}
