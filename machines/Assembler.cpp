#include <machines/machines.h>
#include <factory_structs/BandasTransportadoras.h>
#include <enums.h>

// Constructor
Assembler::Assembler(){
    delay = 0;
    util = new Util();

    dough = new BandasTransportadoras<int>(0);
    chocolate = new BandasTransportadoras<int>(0);
}

// Aqui se reciben los datos para mezclar
// Retorna falso si no se pudo recibir
bool Assembler::receive(MixerType type, int amount){
    bool wasAdded = false;

    if (type == Chocolate){
        wasAdded = chocolate->add(amount);

    } else if (type == Dough){
        wasAdded = dough->add(amount);
    }

    // Si no se pudo agregar es porque una de las bandas se lleno
    if (!wasAdded){
        isRunning = false;
    }

    return wasAdded;
}

// Aqui se envian las galletas al horno
void Assembler::send(){
}

// Aqui se van a ensamblar las galletas
void Assembler::assembly(){

}
