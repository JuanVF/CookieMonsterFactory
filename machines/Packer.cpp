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
    isRunning = false;
    planner = _planner;
    transportadores = _transportadores;
    listaGalletas =  new LinkedList<DepositPacks*>();
}

//Funcion que recibe las galletas
void Packer::receive(int received){
    cout << "La empacadaora ha recibido " << received << endl;
    recibidas += received;
}

//Agregar las galletas
void Packer::agregarPaquete(){
    for (int i=0; i < planner->packs->length; i++){
        PlannerPacks * pack = planner->packs->get(i);

        string _name = pack->getName();
        int total = pack->pack->amountCookies;
        int paquetesTotales = pack->amountPacks;
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
        int divisor = 100 / listaGalletas->length;

        for (int i =0; i < listaGalletas->length; i++){
            probs[i] = QRandomGenerator::global()->bounded(0, divisor);
            listaGalletas->get(i)->probabilidad = probs[i];

            if (i == listaGalletas->length-1){
                int j = 0;

                while (j < listaGalletas->length-1){
                    probs[listaGalletas->length-1] += listaGalletas->get(j)->probabilidad;
                    j++;
                }

                listaGalletas->get(i)->probabilidad =100 - probs[i];
            }
        }
    }
}

int Packer::escogerRandom(){
    int random = QRandomGenerator::global()->bounded(1, 100);
    int sumatoria =0;

    DepositPacks * temp = listaGalletas->get(0);

    if (temp == NULL) return 0;

    sumatoria += temp->probabilidad;

    if (random > 0 && random <= listaGalletas->get(0)->probabilidad){
        return 0;
    }

    for(int i=1; i < listaGalletas->length; i++){
        if ( (random>sumatoria) && (random <= (listaGalletas->get(i)->probabilidad + sumatoria))){
            sumatoria += listaGalletas->get(i)->probabilidad;
            return (i);
        }
    }

    return 0;
}

//Enviar al transporte
DepositPacks * Packer::send(){
    generarRandom();

    int indiceRandom = escogerRandom();

    DepositPacks * temp = listaGalletas->get(indiceRandom);

    if (temp == NULL) return NULL;

    if (temp->cronometro->contadorB()){
        if (!temp->entregaTerminada()){
            temp->entregarPacks();
            string _name = temp->nombre;
            int totalCookies = temp->galletasPorPaquete;
            int _tiempo =0;
            int tp=1;

            cout << "Empacadora: envio un paquete de: " << _name << " de " << totalCookies << endl;
            transportadores->receive(new DepositPacks(_name,totalCookies,_tiempo, tp));
        }
    }

    return NULL;
}

void Packer::removerPacks(){
    for (int i =0; i<listaGalletas->length;i++){
        if (listaGalletas->get(i)->entregaTerminada()){
            listaGalletas->remove(i);
        }

        if (listaGalletas->length == 0){
            isRunning = false;
        }
    }
}

//Mandarle los datos del planner al packer para crear los depositPacks
void Packer::working(){
    if (!isRunning && listaGalletas->length>0)

    agregarPaquete();
    empacar();
    send();
    removerPacks();
}

// Algunos datos de inicializacion para el packer
void Packer::prepare(){
    agregarPaquete();
}

// Retorna info para la UI
string Packer::getInfo(){
    string data = "";

    cout << "Lista de galletas: " << listaGalletas->length << endl;
    for (int i = 0; i < listaGalletas->length; i++){
        DepositPacks * temp = listaGalletas->get(i);

        data += "Paquete: " + temp->nombre + "\n";
        data += "Producidos: " + to_string(temp->actual) + "\n\n";
    }

    return data;
}

void Packer::init(int capacidadBanda, int _capacidad, float _delay){
    bandaEntrada = new BandasTransportadoras<int>(capacidadBanda);
    delay = _delay;
}

bool Packer::canStart(){
    if (bandaEntrada == NULL) return false;

    return bandaEntrada->maxCapacity != 0 && delay != 0;
}
