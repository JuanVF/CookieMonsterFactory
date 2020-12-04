#include <factory_structs/factoryStructs.h>
#include <factory_structs/CookiePack.h>

struct PlannerPacks{
    CookiePack * pack;
    int amountPacks;

    PlannerPacks(string nombre, int amount){
        pack = new CookiePack(amount, nombre);
        amountPacks = 0;
    }

    void addPack(){
        amountPacks++;
    }

    void addPacks(int n){
        amountPacks += n;
    }

    void removePack(){
        if (amountPacks > 0)
            amountPacks--;
    }

    void removePacks(int n){
        amountPacks -= n;
        amountPacks = (amountPacks < 0) ? 0 : amountPacks;
    }

    string getName(){
        return pack->name;
    }

    void changeName(string name){
        pack->name = name;
    }

    void changeAmountCookies(int amount){
        pack->amountCookies = amount;
    }
};
