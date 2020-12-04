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

// Info para la UI
string Assembler::chocolateInfo(){
    Node<int> * temp = chocolate->queue->tail;
    string data = "";

    if (temp == NULL) return data;

    for (int i = 0; i < chocolate->queue->length; i++){
        data += "Num #" + to_string(i) + ", Cant: " + to_string(temp->data) + " gr\n";

        temp = temp->next;
    }

    return data;
}

// Info para la UI
string Assembler::doughInfo(){
    Node<int> * temp = dough->queue->tail;
    string data = "";

    if (temp == NULL) return data;

    for (int i = 0; i < dough->queue->length; i++){
        data += "Num #" + to_string(i) + ", Cant: " + to_string(temp->data) + " gr\n";

        temp = temp->next;
    }

    return data;
}

// Retorna la cantida de chocolate que tiene la banda
int Assembler::amountChocolate(){
    Node<int> * temp = chocolate->queue->tail;
    int amount = 0;

    if (temp == NULL) return 0;

    for (int i = 0; i < chocolate->queue->length; i++){
        amount += temp->data;

        temp = temp->next;
    }

    return amount;
}

// Retorna la cantidad de masa que tiene la banda
int Assembler::amountDough(){
    Node<int> * temp = dough->queue->tail;
    int amount = 0;

    if (temp == NULL) return 0;

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
    bool wasAdded = oven->addCookiesToTrays(amount);

    assembledCookies += amount;

    if (!wasAdded)
        isRunning = false;
}

// Retorna true si pudo ensamblar la galleta
bool Assembler::couldAssembly(){
    int chocolateNeeded = planner->recipe->amountChocolate * capacity;
    int doughNeeded = planner->recipe->amountDough * capacity;

    if (chocolateNeeded - amountChocolate() < 0 && doughNeeded - amountDough() < 0)
        return false;

    // Se vacian las colas
    while (currentChocolate < chocolateNeeded){
        if (chocolate->queue->peek() != NULL)
            currentChocolate += chocolate->get();
        else
            break; // En teoria no deberia llegar aqui
    }

    // Se vacian las colas
    while (currentDough < doughNeeded){
        if (dough->queue->peek() != NULL)
            currentDough += dough->get();
        else
            break; // En teoria no deberia llegar aqui
    }

    currentChocolate = 0;
    currentDough = 0;

    return true;
}

// Aqui se van a ensamblar las galletas
void Assembler::assembly(){
    bool canStart = (started + delay * 1000 - clock() < 0);

    // Esto es que ya paso el delay
    // Y se pudo ensamblar
    if (couldAssembly()){
        if (!canStart) return;

        started = clock();

        send(capacity);
    }
}
