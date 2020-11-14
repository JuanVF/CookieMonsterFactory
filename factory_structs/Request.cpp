#include "../machines/Mixer.h"

struct Request{
    Mixer * mixer;
    int amount;

    Request(Mixer * _mixer, int _amount){
        mixer = _mixer;
        amount = _amount;
    }
};
