#include <lists/CircularList.h>
#include <factory_structs/Cookie.h>
#include <factory_structs/PlannerPacks.h>
#include <machines/machines.h>

// Constructores
Planner::Planner(){
    recipe = new Cookie();
    packs = new CircularList<PlannerPacks *>();
    totalCookies = 0;
}

// Funciones

// Esta es la funcion que se va a encargar de planificar la cantidad total de chocolate y masa a producir
// Tambien la cantidad total de galletas
void Planner::plan(){
    int amount, cookies;
    totalCookies = 0;

    for (int i = 0; i < packs->length; i++){
        cookies = packs->get(i)->pack->amountCookies;
        amount = packs->get(i)->amountPacks;

        totalCookies += cookies * amount;
    }
}

// Esta funcion agrega un nuevo tipo de empaque al plan
// Retorna true si se pudo agregar
bool Planner::addPack(int amountCookies, string name){
    if (findPack(name) != NULL) return false;

    packs->add(new PlannerPacks(name, amountCookies));

    return true;
}

// Esta funcion se encarga de remover un pack de la lista
// Retorna true si se elimino, false de lo contrario
bool Planner::removePack(string name){
    for (int i = 0; i < packs->length; i++){
        if (packs->get(i)->getName() == name){
            packs->remove(i);
            return true;
        }
    }

    return false;
}

// Esta funcion permite settear la cantidad de paquetes a producir
void Planner::setPackAmount(int amount, string name){
    PlannerPacks * pack = findPack(name);

    if (pack == NULL) return;

    pack->addPacks(amount);
}

// Retorna el total de galletas
int Planner::getTotalCookies(){
    return totalCookies;
}

// Esta funcion busca un pack por su nombre y lo retorna
PlannerPacks * Planner::findPack(string name){
    string currentName;

    for (int i = 0; i < packs->length; i++){
        currentName = packs->get(i)->getName();

        if (currentName == name)
            return packs->get(i);
    }

    return NULL;
}
