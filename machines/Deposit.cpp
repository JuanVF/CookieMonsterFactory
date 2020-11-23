#include <factory_structs/CookiePack.h>
#include <factory_structs/BandasTransportadoras.h>
#include <lists/LinkedList.h>

struct Deposit{
    LinkedList<CookiePack *>* galletas;
    int amountProduced;

    Deposit(){       //ap = amount produced
        amountProduced = 0;
        galletas = new LinkedList<CookiePack *>();
    }

    //Le define un int x como cantidad al deposito
    void defineAmountProduced(int num){
        amountProduced = num;
    }

    //Suma al deposito el numero que le coloque de entrada
    void addToDeposit(int num){
        amountProduced += num;
    }


    //Retorna un int con la cantidad que ha recibido el deposito
    int totalInDeposit(){
        return amountProduced;
    }

};
