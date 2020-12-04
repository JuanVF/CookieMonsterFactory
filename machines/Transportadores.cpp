#include <lists/LinkedList.h>
#include <factory_structs/factoryStructs.h>
#include <factory_structs/Transportador.h>
#include <machines/machines.h>

Transportadores::Transportadores(Planner * _planner, Deposit * _deposit){
    transps = new LinkedList<Transportador*>();
    planner = _planner;
    deposit = _deposit;
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

// Esta es la funcion del bucle
void Transportadores::send(){
    Transportador * tran = NULL;
    for (int i = 0; i < transps->length; i++){
        tran = transps->get(i);
        bool canSend = tran->started + delay * 1000 - clock() <= 0;

        if (canSend){
            tran->started = clock();
            deposit->receive(tran->packagesType->getName(), tran->currentPacks);
            tran->currentPacks = 0;
        }
    }
}
