#include <machines/machines.h>

struct Request{
    MixerMachine * mixer;
    int amount;

    // Constructor
    Request(MixerMachine * _mixer, int _amount){
        mixer = _mixer;
        amount = _amount;
    }

    // Info del request
    string toString(){
        string data = "Pedido hacia: " + mixer->name + "\n";
        data += "Cantidad: " + to_string(amount) + "\n";

        return data;
    }
};
