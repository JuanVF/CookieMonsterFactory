#include <lists/dataStructures.h>
#include <factory_structs/factoryStructs.h>
#include <enums.h>
#include <Util.h>

#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
using namespace std;
#endif

#ifndef MACHINES_H
#define MACHINES_H

struct Planner;
struct MixerMachine;
struct WareHouse;
struct Assembler;

// La razon de mover esto aca es por el problema de que la estructura no esta completa
// Esta es la solucion
struct Planner{
    CircularList<PlannerPacks *> * packs;
    Cookie * recipe;
    int totalCookies;

    Planner();

    void plan();
    bool addPack(int amountCookies, string name);
    bool removePack(string name);
    void setPackAmount(int amount, string name);
    int getTotalCookies();
    PlannerPacks * findPack(string name);
};

struct WareHouse{
    DeliveryCar * car;
    Queue<Request*> * requests;
    bool isRunning;
    bool hasChanged;

    WareHouse();
    void setData(double delay, int capacity);
    Request * makeRequest(MixerMachine * mixer, int amount);
    string requestsInfo();
    void sendRequest();
    void checking();
};

struct MixerMachine{
    // Capacidad minima y maxima de la mezcladora
    int min;
    int max;
    int capacity;
    string name;
    double delay; // Tiempo que duran mezclando
    bool isRunning;

    clock_t started;

    MixerType type;
    int amount; // Es la cantidad de masa o chocolate que tiene la mezcladora

    WareHouse * warehouse;
    Assembler * assembler;

    Queue<Request *> * requests;
    LinkedList<Request *> * processed;

    MixerMachine(WareHouse * _warehouse, Assembler * _assembler, MixerType _type, string name);
    void mix();
    void setData(int min, int max, int capacity, double delay);
    void receive(int received);
    void send(int amount);
    void makeRequest();
    bool needsIngredient();
    string requestsProcessedInfo();
    string requestsPendingInfo();
};

struct Assembler{
    bool isRunning;
    double delay;

    int assembledCookies;
    int capacity;

    Util * util;

    BandasTransportadoras<int> * dough;
    BandasTransportadoras<int> * chocolate;

    Assembler();

    void setData(int _dough, int _choc, double _delay, int _capacity);

    bool receive(MixerType type, int amount);
    void send();
    void assembly();
};

#endif
