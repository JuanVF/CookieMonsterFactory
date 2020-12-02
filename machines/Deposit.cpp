#include <factory_structs/CookiePack.h>
#include <factory_structs/BandasTransportadoras.h>
#include <lists/LinkedList.h>
#include <machines/machines.h>


//Contructor
Deposit::Deposit(){       //ap = amount produced
    amountProduced = 0;
    isRunning = false;
    galletas = new LinkedList<CookiePack *>();
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
    return amountProduced;
}

