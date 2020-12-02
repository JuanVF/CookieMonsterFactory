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
struct Oven;
struct Packer;
struct Deposit;
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

    WareHouse();
    Request * makeRequest(MixerMachine * mixer, int amount);
    void sendRequest();
    void checking();
};

struct MixerMachine{
    // Capacidad minima y maxima de la mezcladora
    int min;
    int max;
    int capacity;

    double delay; // Tiempo que duran mezclando
    bool isRunning;

    MixerType type;
    int amount; // Es la cantidad de masa o chocolate que tiene la mezcladora

    WareHouse * warehouse;
    Assembler * assembler;

    Queue<Request *> * requests;

    MixerMachine(WareHouse * _warehouse, Assembler * _assembler, MixerType _type);
    void mix();
    void receive(int received);
    void send(int amount);
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

    Assembler();

    bool receive(MixerType type, int amount);
    void send();
    void assembly();
};

struct Oven{
    BandasTransportadoras<Cookie *> *bandaEntrada;
    LinkedList<Bandeja *> *bandejas ;
    BandasTransportadoras<Cookie *> *bandaSalida ;
    LinkedList<Inspectores *> * inspectores;

    int capacity;
    int cookiesCooked;
    double delay;
    bool isRunning;

    Cronometro * cronometro;

    Oven(int capacidadHorno, int capacidadBanda, double _delay);

    void restartOven();
    void addCookiesToTrays(int num);
    void modifyCapacity(int newCap);
    int galletasHorneadas();
    int send(int waitingTime);

};

struct Packer{
    int capacity;
    int content;
    bool isRunning;

    Planner * planner;

    Packer(int _c, Planner * planner);

    void addCapacity(int new_capacity);
    void destroyContent();
    int sobrante(int received);
    void receive(int received);
    void send();;

};

struct Deposit{
    LinkedList<CookiePack *>* galletas;
    int amountProduced;
    bool isRunning;

    Deposit();

    void defineAmountProduced(int num);
    void addToDeposit(int num);
    int totalInDeposit();
};

#endif

