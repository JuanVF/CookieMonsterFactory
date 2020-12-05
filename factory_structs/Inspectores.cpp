#include <QRandomGenerator>
#include <lists/LinkedList.h>
#include <factory_structs/factoryStructs.h>


// El prob debe estar entre 0-100
Inspectores::Inspectores(){
    prob = 0;
    rechazadas = 0;
    aprobadas = 0;
}

void Inspectores::init(float _prob){
    prob = _prob;
}

bool Inspectores::canStart(){
    return prob != 0;
}

// Retorna la cantidad de galletas que se deben enviar
int Inspectores::evaluate(int cookiesReceived){
    int total = 0;
    float random;

    for (int i = 0; i < cookiesReceived; i++){
        random = QRandomGenerator::global()->bounded(15);

        if (random > prob){
            total++;
        }
    }

    return total;
}
