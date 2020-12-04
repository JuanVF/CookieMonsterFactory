#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
using namespace std;
#endif

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif

#ifndef FACTORYSTRUCTS_H
#define FACTORYSTRUCTS_H

template <typename Data>
struct BandasTransportadoras;
struct Bandeja;
struct CookiePack;
struct DeliveryCar;
struct Inspectores;
struct PlannerPacks;
struct Request;
struct Transportador;
struct DepositPacks;
struct Cronometro;
struct Cookie;

struct DepositPacks{
    string nombre;

    int tiempo;
    int actual;
    int galletasPorPaquete;

    int paquetesActuales;
    int totalPaquetes;

    int probabilidad;

    DepositPacks(string _nombre, int _galletasTotal, int _tiempo, int tp);
    void agregarGalletas(int num);
    void cambiarProbabilidad(int np);
    bool isFinished();
};
struct Cronometro{
    int segundos = 0;
    double limite;
    clock_t time;

    Cronometro(double _limit);

    bool contadorB();
};
struct Cookie{
    int amountDough;
    int amountChocolate;
    string measure;

    Cookie();

    void setData(double _amountDough, double _amountChocolate);
};
#endif
