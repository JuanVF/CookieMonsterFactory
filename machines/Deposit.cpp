#include <factory_structs/CookiePack.h>
#include <factory_structs/BandasTransportadoras.h>
#include <lists/LinkedList.h>
#include <machines/machines.h>


//Contructor
Deposit::Deposit(Planner * _planner){       //ap = amount produced
    amountProduced = 0;
    isRunning = false;
    galletas = new LinkedList<CookiePack *>();
    planner = _planner;

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

