#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
using namespace std;
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

    int paquetesEntregados =0;
    Cronometro * cronometro;

    DepositPacks(string _nombre, int _galletasTotal, int _tiempo, int tp);
    void agregarGalletas(int num);
    void entregarPacks();

    bool isFinished();
    bool entregaTerminada();
};
struct Cronometro{
    int segundos = 0;
    double limite;

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
