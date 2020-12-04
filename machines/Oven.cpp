#include <factory_structs/factoryStructs.h>
#include <factory_structs/Bandeja.h>
#include <factory_structs/Cookie.h>
#include <factory_structs/BandasTransportadoras.h>
#include <lists/LinkedList.h>
#include <machines/machines.h>


//Contructor
Oven::Oven(){
    bandejas = new LinkedList<Bandeja *>();

    for (int i=0; i<6; i++){
        bandejas->add(new Bandeja());
    }

    inspectores = new LinkedList<Inspectores *>();
    isRunning = false;
    cookiesCooked = 0;
}

void Oven::init(int capacidadHorno, int capacidadBanda, double _delay){
    bandaSalida = new BandasTransportadoras<int>(capacidadBanda);
    bandaEntrada = new BandasTransportadoras<int>(capacidadBanda);

    capacity = capacidadHorno;
}

//Su proposito es que cada vez que se manden galletas al empacador, se reinicie el total (empiece desde 0)
void Oven::restartOven(){
    cookiesCooked = 0;
}

//Esta funcion esta hecha para agregar galletas en el horno
bool Oven::addCookiesToTrays(int num){
    for (int i = 0; i < bandejas->length; i++){
        if (bandejas->get(i)->sobrantes(num)== 0 and bandejas->get(i)->state){
            bandejas->get(i)->agregarGalletas(num);
            return true;

        }else if ((num)+bandejas->get(i)->quantity>bandejas->get(i)->capacity and bandejas->get(i)->state){
            bandejas->get(i)->quantity = bandejas->get(i)->capacity;
            if ((i+1)< (bandejas->length)){
                bandejas->get(i+1)->agregarGalletas(bandejas->get(i)->sobrantes(num));
                return true;
            }
            else{
                //apagar la maquina ensambladora
                return false;
            }
        }
    }

    return false;
}


//Esta funcion sirve para modificar la capacidad del horno
void Oven::modifyCapacity(int newCap){
    capacity = newCap;
}

//Cambia el tiempo del cronometro
void Oven::changeTrayTiming(int ind,double num){
    if (ind<6 and ind >=0){
        bandejas->get(ind)->cronometro->limite = num;
    }
}

//Funcion temporal (Probablemente despues usemos una que funcione con tiempo real)
int Oven::galletasHorneadas(){
    return cookiesCooked;
}


//Esta funcion sirve para retornar su capacidad
int Oven::send(){
    int total = 0;
    for (int i =0; i<bandejas->length;i++){
        if (bandejas->get(i)->state == true){
            if (bandejas->get(i)->cronometro->contadorB() == true){
                total+= bandejas->get(i)->quantity;
                bandejas->get(i)->vaciarBandeja();
            }
        }
    }
    bandaSalida->agregarIndividual(total);
    return total;
}

void Oven::apagarBandejas(int indiceBandeja){
    if (indiceBandeja<6 and indiceBandeja>1){
        bandejas->get(indiceBandeja)->turnOff();
    }
}

int Oven::galletasEnEspera(){
    int wc = bandaEntrada->length; //wc significa waiting cookies//
    return wc;
}

int Oven::galletasCocinadas(int ind){
    if (ind<bandejas->length){
        return bandejas->get(ind)->quantity;
    }
    return 0;
}

int Oven::totalGalletas(){
    int total = 0;
    for (int i =0; i<bandejas->length;i++){
        total+= bandejas->get(i)->quantity;
    }
    return total;
}

