#include <factory_structs/factoryStructs.h>
#include <machines/machines.h>
#include <QRandomGenerator>
#include <factory_structs/CookiePack.h>
#include <factory_structs/Inspectores.h>
#include <factory_structs/PlannerPacks.h>
#include <factory_structs/DepositPacks.h>
#include <factory_structs/BandasTransportadoras.h>

//Contructor
Packer::Packer(Planner * _planner, Transportadores * _transportadores){
    recibidas = 0;
    delay = 0;
    isRunning = false;
    planner = _planner;
    transportadores = _transportadores;
    listaGalletas =  new LinkedList<DepositPacks*>();
}

void Packer::init(int capacidadBanda, int _capacidad, float _delay){
    bandaEntrada = new BandasTransportadoras<int>(capacidadBanda);
    delay = _delay;

}

void Packer::start(){
    if (!isRunning) return;

    send();
}

//Funcion que recibe las galletas
void Packer::receive(int received){
    recibidas += received;
}

//Agregar las galletas
void Packer::agregarPaquete(){
    for (int i=0; i<listaGalletas->length;i++){
        string _name = planner->packs->get(i)->getName();
        int total = planner->packs->get(i)->pack->amountCookies;
        int paquetesTotales =planner->packs->get(i)->amountPacks;
        int _delay = 5;
        listaGalletas->add(new DepositPacks(_name, total, _delay, paquetesTotales));
    }
}

//Cambiar tiempo de empaque de las galletas
void Packer:: cambiarDelay(string _name, int newTime){
    for (int i=0; i<listaGalletas->length;i++){
        if (listaGalletas->get(i)->nombre == _name){
            listaGalletas->get(i)->tiempo = newTime;
        }
    }
}

//
void Packer::addCookies(string name, int num){
    for (int i=0; i< listaGalletas->length; i++){
        if (listaGalletas->get(i)->nombre == name){
            listaGalletas->get(i)->agregarGalletas(num);
        }
    }
}

void Packer::generarRandom(){
    int probs[listaGalletas->length];
    int divisor = 100/listaGalletas->length ;

    for (int i =0;i<listaGalletas->length;i++){
        probs[i]= QRandomGenerator::global()->bounded(0,divisor);

        listaGalletas->get(i)->probabilidad = probs[i];

        if (i == listaGalletas->length-1){
            int j = 0;
            while (j<listaGalletas->length-1){
                probs[listaGalletas->length-1] += listaGalletas->get(j)->probabilidad;
                j++;
            }
            listaGalletas->get(i)->probabilidad =100 - probs[i];
        }
    }
}

//Enviar al transporte
void Packer::send(){

    for (int i =0; i<planner->packs->length;i++){
        string _name = planner->packs->get(i)->getName();
        int _galletasP = planner->packs->get(i)->amountPacks;
        //int _delay =  tiempo
        //listaGalletas->add();
    }
}

