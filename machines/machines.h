#include <lists/dataStructures.h>
#include <factory_structs/factoryStructs.h>
#include <enums.h>
#include <Util.h>

#ifndef MACHINES_H
#define MACHINES_H
struct Planner;
struct MixerMachine;
struct WareHouse;
struct Assembler;

// La razon de mover esto aca es por el problema de que la estructura no esta completa
// Esta es la solucion
struct WareHouse{
    DeliveryCar * car;
    Queue<Request*> * requests;
    bool isRunning;

    WareHouse(int carCapacity, int carDelay);
    Request * makeRequest(MixerMachine * mixer, int amount);
    void sendRequest();
    void checking();
};

struct MixerMachine{
    // Capacidad minima y maxima de la mezcladora
    int min;
    int max;
    int id;

    double delay; // Tiempo que duran mezclando
    bool isRunning;
    bool isStarting;

    MixerType type;
    int amount; // Es la cantidad de masa o chocolate que tiene la mezcladora

    WareHouse * warehouse;
    Queue<Request *> * requests;

    MixerMachine(WareHouse * _warehouse, int _id, double _delay, int _min, int _max, MixerType _type);
    void mix();
    void receive(int received);
    void makeRequest();
    bool needsIngredient();
};

struct Assembler{
    bool isRunning;
    double delay;

    int assembledCookies;

    Util * util;

    BandasTransportadoras<int> * dough;
    BandasTransportadoras<int> * chocolate;

    Assembler(double _delay, int _doughCapacity, int chocolateCapacity);

    bool receive(MixerType type, int amount);
    void send();
    void assembly();
};

#endif
