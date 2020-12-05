#include <lists/LinkedList.h>
#include <factory_structs/factoryStructs.h>
#include <machines/machines.h>
#include <factory_structs/PlannerPacks.h>
#include <factory_structs/BandasTransportadoras.h>


//Contructor
Deposit::Deposit(Planner * _planner){       //ap = amount produced
    amountProduced = 0;
    isRunning = false;
    galletas = new LinkedList<PlannerPacks *>();
    planner = _planner;
}

void Deposit::init(){
    // Se crean la cantidad de galletas a recibir
    for (int i = 0; i < planner->packs->length; i++){
        PlannerPacks * temp = planner->packs->get(i);

        galletas->add(new PlannerPacks(temp->getName(), temp->pack->amountCookies));
    }
}

// Aqui se reciben los datos
bool Deposit::receive(string name, int amount){
    PlannerPacks * temp = findByName(name);
    if (temp == NULL) return false;

    temp->addPacks(amount);
}

string Deposit::getInfo(){
    string data = "";

    for (int i = 0; i < galletas->length; i++){
        PlannerPacks * current = galletas->get(i);

        data += "Paquete: " + current->getName() + "\n";
        data += "Recibidos: " + to_string(current->amountPacks) + "\n";
    }

    return data;
}

// Busca un paquete por su nombre
PlannerPacks * Deposit::findByName(string name){
    for (int i = 0; i < galletas->length; i++){
        PlannerPacks * temp = galletas->get(i);

        if (temp->getName() == name) return temp;
    }

    return NULL;
}

//Le define un int x como cantidad al deposito
void Deposit::defineAmountProduced(int num){
    amountProduced = num;
}

//Suma al deposito el numero que le coloque de entrada
void Deposit::addToDeposit(int num){
    amountProduced += num;
}


//Retorna un int con la cantidad que ha recibido el deposito
int Deposit::totalInDeposit(){
    int amount = 0;

    for (int i = 0; i < galletas->length; i++){
        amount += galletas->get(i)->amountPacks;
    }

    return amount;
}

