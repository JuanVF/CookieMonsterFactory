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
struct Cookie{
    int amountDough;
    int amountChocolate;
    string measure;

    Cookie();

    void setData(double _amountDough, double _amountChocolate);
};
struct CookiePack;
struct DeliveryCar;
struct Inspectores;
struct PlannerPacks;
struct Request;
struct Transportador;
struct Transportadores;
struct Cronometro;
#endif
