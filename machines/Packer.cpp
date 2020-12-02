#include <machines/Oven.h>
#include <factory_structs/Inspectores.h>
#include <factory_structs/CookiePack.h>
#include <factory_structs/BandasTransportadoras.h>
#include <factory_structs/Transportadores.h>
#include <machines/machines.h>


//Contructor
Packer::Packer(int _c, Planner * _planner){
    capacity = _c;
    content = 0;
    isRunning = false;
    planner = _planner;
}

//Aumentar la capacidad
void Packer::addCapacity(int new_capacity){
    capacity += new_capacity;
}

//Destruit contenido
void Packer::destroyContent(){
    content = 0;
}

//Retorna un int con la cantidad que sobro
int Packer::sobrante(int received){
    if (received>capacity){
        int acumulado = received - capacity;
        return acumulado;
    }
    else
        return 0;
}

//Funcion que recibe las galletas
void Packer::receive(int received){
    if (received<=capacity and (received+content)<=capacity and isRunning){
        content += received;
    }
    else if ((received+content)>capacity){
        while ((received+content)>capacity){
            received-=1;
        }
        content+=received;
    }
}

//Enviar al transporte
void Packer::send(){
    for (int i =0; i<planner->packs->length;i++){

    }
}

