#include <lists/dataStructures.h>
#include <factory_structs/factoryStructs.h>
#include <enums.h>
#include <Util.h>
#include <lists/CircularList.h>

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
    void reset();
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
    void reset();
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
    void reset();
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

    int currentDough;
    int currentChocolate;

    clock_t started;

    Planner * planner; // Se necesita al planner para la receta
    Oven * oven;

    BandasTransportadoras<int> * dough;
    BandasTransportadoras<int> * chocolate;

    Assembler(Oven * _oven, Planner * _planner);

    void setData(int _dough, int _choc, double _delay, int _capacity);
    void reset();
    void send(int amount);
    void assembly();
    bool receive(MixerType type, int amount);
    bool couldAssembly();
    int amountChocolate();
    int amountDough();
    string chocolateInfo();
    string doughInfo();
};

struct Oven{
    BandasTransportadoras<int> *bandaEntrada;
    LinkedList<Bandeja *> *bandejas ;
    BandasTransportadoras<int> *bandaSalida ;
    LinkedList<Inspectores *> * inspectores;

    int capacity;
    int cookiesCooked;
    double delay;
    bool isRunning;

    Cronometro * cronometro;

    Oven();

    void init(int capacidadHorno, int capacidadBanda, double _delay);
    void restartOven();
    bool addCookiesToTrays(int num);
    void modifyCapacity(int newCap);
    int galletasHorneadas();
    int send(int waitingTime);
    void apagarBandejas(int indiceBandeja);
    int galletasEnEspera();
    int galletasCocinadas(int ind);
    int totalGalletas();


};

struct Packer{
    int recibidas;
    bool isRunning;
    BandasTransportadoras<int> *bandaEntrada;
    Planner * planner;
    Transportadores * transportadores;
    LinkedList<DepositPacks* >* listaGalletas;

    Packer(Planner * _planner, Transportadores * _transportadores);

    void init(int _c);
    void addCapacity(int new_capacity);
    void destroyContent();
    void receive(int received);
    void agregarPaquete();
    void cambiarDelay(string _name, int newTime);
    void addCookies(string name, int num);
    void send();
};

struct Deposit{
    LinkedList<CookiePack *>* galletas;
    int amountProduced;
    bool isRunning;
    Planner * planner;

    Deposit(Planner * planner);

    void defineAmountProduced(int num);
    void addToDeposit(int num);
    int totalInDeposit();
};

#endif

