#include <factory_structs/Bandeja.h>
#include <factory_structs/Inspectores.h>
#include <factory_structs/Cookie.h>
#include <factory_structs/BandasTransportadoras.h>
#include <lists/LinkedList.h>

struct Oven{
    BandasTransportadoras<Cookie *> *cookies ;
    LinkedList<Bandeja *> *bandejas ;
    LinkedList<Inspectores *> * inspectores;

    int capacity;
    int totalCookiesCooked;
    double delay;

    Oven(int _capacity, int _maxc, int _length){
        cookies = new BandasTransportadoras<Cookie *>(_maxc, _length);

        bandejas = new LinkedList<Bandeja *>();
        for (int i=0; i<6; i++){
            bandejas->add(new Bandeja());
        }

        inspectores = new LinkedList<Inspectores *>();
        capacity = _capacity;
        totalCookiesCooked = 0;
        delay = 60;

    }

    //Su proposito es que cada vez que se manden galletas al empacador, se reinicie el total
    void restartCookiesCooked(){
        totalCookiesCooked = 0;
    }

    //Esta funcion esta hecha para sumar galletas al total cocinadas
    void addCookiesCooked(int num){
        totalCookiesCooked += num;
    }


    //Esta funcion sirve para modificar la capacidad del horno
    void modifyCapacity(int newCap){
        capacity = newCap;
    }


    //Funcion temporal (Probablemente despues usemos una que funcione con tiempo real)
    int galletasHorneadas(){
        return totalCookiesCooked;
    }

    //---------------------------------------------------------------------------------------
    //Esta funcion sirve para usarla como un temporizador
    //La variable x representa el tiempo actual que lleva la galleta en el horno
    //Se puede implementar con un while o al menos nose como lo piense usted
    //En esta progra nos va a servir
    bool temporizador(int x){
        if (x>=delay){
            return true;
        }
        else{
           //x++;
        }
        return false;
    }

    //Esta funcion sirve para retornar su capacidad
    int send(int time){
        if (temporizador( time) == true){
            return capacity;
        }
        else
            return 0;
    }
    //----------------------------------------------------------------------------------------

};
