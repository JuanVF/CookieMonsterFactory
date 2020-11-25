#include <machines/machines.h>
#include <factory_structs/BandasTransportadoras.h>
#include <enums.h>

// Constructor
Assembler::Assembler(double _delay, int _doughCapacity, int _chocolateCapacity){
    delay = _delay;
    util = new Util();

    dough = new BandasTransportadoras<int>(_doughCapacity);
    chocolate = new BandasTransportadoras<int>(_chocolateCapacity);
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
