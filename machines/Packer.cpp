#include <machines/Oven.h>
#include <factory_structs/Inspectores.h>


struct Packer{
    int capacity;
    int content;

    Packer(int _c){
        capacity = _c;
        content = 0;
    }

    void addCapacity(int new_capacity){
        capacity += new_capacity;
    }

    void destroyContent(){
        content = 0;
    }

    //
    int sobrante(int received){
        if (received>capacity){
            int acumulado = received - capacity;
            return acumulado;
        }
        else
            return 0;
    }

    //
    void receive(int received){
        if (received<=capacity and (received+content)<=capacity){
            content += received;
        }
        else if ((received+content)>capacity){
            while ((received+content)>capacity){
                received-=1;
            }
            content+=received;
        }

    }

    //
    void send();

};
