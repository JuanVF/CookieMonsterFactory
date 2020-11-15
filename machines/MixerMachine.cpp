#include <lists/Queue.h>
#include <factory_structs/factoryStructs.h>
#include <machines/Warehouse.h>

struct MixerMachine{
    // Capacidad minima y maxima de la mezcladora
    int min;
    int max;
    int id;

    double delay; // Tiempo que duran mezclando

    int type; // Si es 0 es de chocolate, si es 1 es de masa
    int amount; // Es la cantidad de masa o chocolate que tiene la mezcladora

    WareHouse * warehouse;
    Queue<Request *> * requests;

    // Constructor
    MixerMachine(WareHouse * _warehouse, int _id, double _delay, int _min, int _max, int _type){
        delay = _delay;
        min = _min;
        max = _max;
        type = _type;
        amount = 0;
        id = _id;

        warehouse = _warehouse;
        requests = new Queue<Request *>();
    }

    // Funciones

    // Esta es la funcion que se va encargar de mezclar
    void mix(){

    }

    // Esta funcion recibe la solicitud que le hizo al almacen
    void receive(int received){
        amount += received;

        // Se limita por si se llega al maximo
        if (amount > max) amount = max;

        requests->dequeue();
    }

    // Esta funcion hace una peticion al almacen
    void makeRequest(){
        int toRequest = max - amount;

        Request * req = warehouse->makeRequest(this, toRequest);

        requests->enqueue(req);
    }

    // Retorna true si necesita ingrediente
    bool needsIngredient(){
        return amount < max;
    }
};
