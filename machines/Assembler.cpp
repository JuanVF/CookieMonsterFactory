#include <machines/machines.h>
#include <factory_structs/BandasTransportadoras.h>
#include <enums.h>

// Constructor
Assembler::Assembler(Oven * _oven, Planner * _planner){
    delay = 0;

    planner = _planner;
    oven = _oven;

    dough = new BandasTransportadoras<int>(0);
    chocolate = new BandasTransportadoras<int>(0);
}

void Assembler::setData(int _dough, int _choc, double _delay, int _capacity){
    dough->maxCapacity = _dough;
    chocolate->maxCapacity = _choc;
    delay = _delay;
    capacity = _capacity;

    started = clock();
}

// Resetea los datos de la maquina
void Assembler::reset(){
    while(dough->queue->dequeue() != NULL);
    while(chocolate->queue->dequeue() != NULL);
    chocolate->length = 0;
    dough->length = 0;
}

// Retorna la cantida de chocolate que tiene la banda
int Assembler::amountChocolate(){
    Node<int> * temp = dough->queue->tail;
    int amount = 0;

    if (temp == NULL) return amount;


    for (int i = 0; i < dough->queue->length; i++){
        amount += temp->data;

        temp = temp->next;
    }

    return amount;
}

// Retorna la cantidad de masa que tiene la banda
int Assembler::amountDough(){
    Node<int> * temp = dough->queue->tail;
    int amount = 0;

    if (temp == NULL) return amount;


    for (int i = 0; i < dough->queue->length; i++){
        amount += temp->data;

        temp = temp->next;
    }

    return amount;
}

// Aqui se reciben los datos para mezclar
// Retorna falso si no se pudo recibir
bool Assembler::receive(MixerType type, int amount){
    bool wasAdded = false;

    if (type == Chocolate){
        wasAdded = chocolate->add(amount);

    } else if (type == Dough){
        wasAdded = dough->add(amount);
    }

    // Si no se pudo agregar es porque una de las bandas se lleno
    if (!wasAdded){
        isRunning = false;
    }

    return wasAdded;
}

// Aqui se envian las galletas al horno
void Assembler::send(int amount){
    // TODO: Si retorna false apagar la maquina
    //bool wasAdded = oven->send(amount);
    bool wasAdded = true;

    if (!wasAdded)
        isRunning = false;
}

// Retorna true si pudo ensamblar la galleta
bool Assembler::couldAssembly(){
    int chocolateNeeded = planner->recipe->amountChocolate * capacity;
    int doughNeeded = planner->recipe->amountDough * capacity;

    currentChocolate += chocolate->get();
    currentDough += dough->get();

    if (chocolateNeeded - currentChocolate < 0 && doughNeeded - currentDough < 0)
        return false;

    currentChocolate = 0;
    currentDough = 0;

    return true;
}

// Aqui se van a ensamblar las galletas
void Assembler::assembly(){
    bool canStart = (started + delay * 1000 - clock());

    // Esto es que ya paso el delay
    // Y se pudo ensamblar
    if (canStart && couldAssembly()){
        started = clock();

        send(capacity);
    }
}
