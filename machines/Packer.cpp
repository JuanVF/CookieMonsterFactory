#include <factory_structs/factoryStructs.h>
#include <machines/machines.h>
#include <QRandomGenerator>
#include <factory_structs/CookiePack.h>
#include <factory_structs/Cronometro.h>
#include <factory_structs/Inspectores.h>
#include <factory_structs/PlannerPacks.h>
#include <factory_structs/DepositPacks.h>
#include <factory_structs/BandasTransportadoras.h>

//Contructor
Packer::Packer(Planner * _planner, Transportadores * _transportadores){
    recibidas = 0;
    isRunning = false;
    planner = _planner;
    transportadores = _transportadores;
    listaGalletas =  new LinkedList<DepositPacks*>();
}

void Packer::init(int capacidadBanda){
    bandaEntrada = new BandasTransportadoras<int>(capacidadBanda);
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

void Packer::addCookies(string name, int num){
    for (int i=0; i<listaGalletas->length;i++){
        if (listaGalletas->get(i)->nombre == name){
            listaGalletas->get(i)->agregarGalletas(num);
        }
        if (listaGalletas->get(i)->isFinished() and (listaGalletas->get(i)->actual)>0){
            recibidas += listaGalletas->get(i)->actual;
            listaGalletas->get(i)->actual = 0;
        }
    }
}

void Packer::empacar(){
    for (int i=0; i<listaGalletas->length;i++){
        string nombrePaquete = listaGalletas->get(i)->nombre;
        addCookies(nombrePaquete,recibidas);
    }
}

void Packer::generarRandom(){
    if(listaGalletas->length>0){
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
}

/*
void Packer::generarRandom(){
    int probs[listaGalletas->length];
    int divisor = 100/listaGalletas->length;
    if (listaGalletas->length>0)
*/

int Packer::escogerRandom(){
    int random = QRandomGenerator::global()->bounded(1,100);
    int sumatoria =0;
    sumatoria += listaGalletas->get(0)->probabilidad;
    if (random>0 and random<=listaGalletas->get(0)->probabilidad){
        return 0;
    }
    for(int i=1; i<listaGalletas->length;i++){
        if ((random>sumatoria) and (random<=(listaGalletas->get(i)->probabilidad+sumatoria))){
            sumatoria += listaGalletas->get(i)->probabilidad;
            return (i);
        }
    }
}

//Enviar al transporte
DepositPacks Packer::send(){
    generarRandom();
    int indiceRandom = escogerRandom();
    if (listaGalletas->get(indiceRandom)->cronometro->contadorB() == true){
        if (!listaGalletas->get(indiceRandom)->entregaTerminada()){
            while (isRunning){
                listaGalletas->get(indiceRandom)->entregarPacks();
                string _name = listaGalletas->get(indiceRandom)->nombre;
                int totalCookies = listaGalletas->get(indiceRandom)->galletasPorPaquete;
                int _tiempo =0;
                int tp=1;
                return DepositPacks(_name,totalCookies,_tiempo, tp);
            }
        }
    }
}

void Packer::removerPacks(){
    for (int i =0; i<listaGalletas->length;i++){
        if (listaGalletas->get(i)->entregaTerminada()==true){
            listaGalletas->remove(i);
        }
        if (listaGalletas->length == 0){
            isRunning = false;
        }
    }
}

//Mandarle los datos del planner al packer para crear los depositPacks
void Packer::working(int galletasEntrantes){
    while (isRunning and listaGalletas->length>0){
        agregarPaquete();
        receive(galletasEntrantes);
        empacar();
        send();
        removerPacks();
    }
}


