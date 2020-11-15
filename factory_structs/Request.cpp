#include <machines/machines.h>

struct Request{
    MixerMachine * mixer;
    int amount;

    // Constructor
    Request(MixerMachine * _mixer, int _amount){
        mixer = _mixer;
        amount = _amount;
    }
};
