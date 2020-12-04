#include <lists/LinkedList.h>
#include <factory_structs/factoryStructs.h>
#include <factory_structs/Transportador.h>
#include <machines/machines.h>

Transportadores::Transportadores(Planner * _planner, Deposit * _deposit){
    transps = new LinkedList<Transportador*>();
    planner = _planner;
    deposit = _deposit;
    isRunning = false;
}

// Llamar a esta funcion antes de iniciar la simulacion
void Transportadores::init(){
    // Inicializamos los transportadores
    for (int i = 0; i < planner->packs->length; i++){
        PlannerPacks * pack = planner->packs->get(i);

        transps->add(new Transportador(pack));
        transps->get(i)->initTime();
    }
}

void Transportadores::setData(int _capacity, float _delay){
    capacity = capacity;
    delay = _delay;
}

// Esta funcion recibe los datos de la maquina
bool Transportadores::receive(DepositPacks * received){
    Transportador * trans = findByName(received->nombre);

    if (trans == NULL) return false;

    bool canSend = trans->started + delay * 1000 - clock() <= 0;

    if (trans->currentPacks >= capacity && !canSend) return false;

    int amount = received->totalPaquetes;

    if (amount >= capacity){
        amount = capacity;
    }

    trans->currentPacks += amount;

    received->totalPaquetes = (received->totalPaquetes - amount < 0) ? 0 : received->totalPaquetes - amount;

    return true;
}

// Llamar a esta funcion para eliminar a los transportadores
void Transportadores::reset(){
    // Se vacia la lista de transportadores
    while(transps->removeFirst() != NULL);
}

// Devuelve un transportador por su nombre
Transportador * Transportadores::findByName(string name){
    Transportador * temp = NULL;

    for (int i = 0; i < transps->length; i++){
        temp = transps->get(i);
        if (temp->packagesType->getName() == name) return temp;
    }

    return NULL;
}

// Inicializa los relojes de los transportadores
void Transportadores::initClocks(){
    Transportador * tran = NULL;

    for (int i = 0; i < transps->length; i++){
        tran = transps->get(i);

        tran->initTime();
    }
}

// Esta es la funcion del bucle
void Transportadores::send(){
    if (!isRunning) return;

    Transportador * tran = NULL;
    for (int i = 0; i < transps->length; i++){
        tran = transps->get(i);
        bool canSend = tran->started + delay * 1000 - clock() <= 0;

        // Esto verifica que ya paso el tiempo y que no vaya a enviar 0
        if (canSend && tran->currentPacks > 0){
            tran->started = clock();
            deposit->receive(tran->packagesType->getName(), tran->currentPacks);
            tran->currentPacks = 0;
        }
    }
}
