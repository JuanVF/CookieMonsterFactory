#include "../lists/CircularList.h"

#include "../factory_structs/Cookie.h"
#include "../factory_structs/PlannerPacks.h"

struct Planner{
    CircularList<PlannerPacks *> * packs;
    Cookie * recipe;

    int totalCookies;

    // Constructores
    Planner(int amountDough, int amountChocolate){
        recipe = new Cookie(amountDough, amountChocolate);
        packs = new CircularList<PlannerPacks *>();

        totalCookies = 0;
    }

    // Funciones

    // Esta es la funcion que se va a encargar de planificar la cantidad total de chocolate y masa a producir
    // Tambien la cantidad total de galletas
    void plan(){
        int amount, cookies;

        for (int i = 0; i < packs->length; i++){
            cookies = packs->get(i)->pack->amountCookies;
            amount = packs->get(i)->amountPacks;

            totalCookies += cookies * amount;
        }
    }

    // Esta funcion agrega un nuevo tipo de empaque al plan
    // Retorna true si se pudo agregar
    bool addPack(int amountCookies, string name){
        if (findPack(name) != NULL) return false;

        packs->add(new PlannerPacks(name, amountCookies));

        return true;
    }

    // Esta funcion permite settear la cantidad de paquetes a producir
    void setPackAmount(int amount, string name){
        PlannerPacks * pack = findPack(name);

        if (pack == NULL) return;

        pack->addPacks(amount);
    }

    int getTotalCookies(){
        return totalCookies;
    }

    // Esta funcion busca un pack por su nombre y lo retorna
    PlannerPacks * findPack(string name){
        string currentName;

        for (int i = 0; i < packs->length; i++){
            currentName = packs->get(i)->pack->name;

            if (currentName == name)
                return packs->get(i);
        }

        return NULL;
    }
};
