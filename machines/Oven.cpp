#include <lists/LinkedList.h>
#include <factory_structs/factoryStructs.h>
#include <machines/machines.h>
#include <factory_structs/Bandeja.h>
#include <factory_structs/Cookie.h>
#include <factory_structs/BandasTransportadoras.h>

//Contructor
Oven::Oven(Packer * _packer){
    bandejas = new LinkedList<Bandeja *>();
    packer = _packer;

    for (int i=0; i<6; i++){
        bandejas->add(new Bandeja());
    }

    inspectores = new LinkedList<Inspectores *>();
    isRunning = false;
    cookiesCooked = 0;

}

// Esto es para settear los datos desde la
// La razon es porque el horno se crea apenas se crea la UI entonces no se pueden settear los datos ahi
void Oven::init(int capacidadHorno, int capacidadBanda, LinkedList<float> * traysDelay, LinkedList<int> * traysCap){
    bandaSalida = new BandasTransportadoras<int>(capacidadBanda);
    bandaEntrada = new BandasTransportadoras<int>(capacidadBanda);

    capacity = capacidadHorno;

    // Se modifica la capacidad de cada bandeja
    for (int i = 0; i < bandejas->length; i++){
        Bandeja * temp = bandejas->get(i);
        temp->modifyCapacity(traysCap->get(i));
        changeTrayTiming(i, traysDelay->get(i));
    }

    // Dos siempre deben estar encendidas
    bandejas->get(0)->state = true;
    bandejas->get(1)->state = true;
}

void Oven::start(){
    if (!isRunning) return;

    int toSend = send();

    if (toSend != 0){
        cout << "El Horno ha enviado : " << toSend << endl;
        packer->receive(toSend);
    }
}

//Esta funcion sirve para retornar su capacidad
int Oven::send(){
    int total = 0;

    for (int i =0; i<bandejas->length;i++){
        if (bandejas->get(i)->state){

            if (bandejas->get(i)->cronometro->contadorB()){
                total += bandejas->get(i)->quantity;
                cookiesCooked += total;
                bandejas->get(i)->vaciarBandeja();
            }
        }
    }

    bandaSalida->agregarIndividual(total);

    return total;
}

//Su proposito es que cada vez que se manden galletas al empacador, se reinicie el total (empiece desde 0)
void Oven::restartOven(){
    cookiesCooked = 0;
}

//Esta funcion esta hecha para agregar galletas en el horno
bool Oven::addCookiesToTrays(int num){
    cout << "El horno ha recibido: " << num << endl;

    for (int i = 0; i < bandejas->length; i++){
        Bandeja * band = bandejas->get(i);

        if (band == NULL) continue;

        int capacidadBandeja = bandejas->get(i)->capacity;
        bool estadoBandeja = bandejas->get(i)->state;
        bool bandejaOcupada = ((num) + band->quantity) > capacidadBandeja && estadoBandeja;

        if (band->sobrantes(num) == 0 && estadoBandeja){
            cout << "Horno: La bandeja #" << i + 1 << " ha recibido "  << num << endl;
            band->agregarGalletas(num);
            cout << "La bandeja #" << i + 1 << " tiene: " << band->quantity << endl;
            return true;

        } else if (bandejaOcupada){
            band->quantity = band->capacity;

            for (int j = i + 1; j < bandejas->length; j++){
                Bandeja * bandN = bandejas->get(j);

                if (bandN == NULL) continue;

                if (bandN->state){
                    cout << "Horno: La bandeja #" << j + 1 << " ha recibido "  << num << endl;
                    bandN->agregarGalletas(band->sobrantes(num));
                    cout << "La bandeja #" << j + 1 << " tiene: " << bandN->quantity << endl;
                    return true;

                } else {
                    cout << "Horno: Orden de " << num << " ha sido encolada..." << endl;
                    return bandaEntrada->agregarIndividual(num) != 1;
                }
            }
        }
    }
    cout << "Horno: Orden de " << num << " ha sido rechazada..." << endl;

    return false;
}


//Esta funcion sirve para modificar la capacidad del horno
void Oven::modifyCapacity(int newCap){
    capacity = newCap;
}

//Cambia el tiempo del cronometro
void Oven::changeTrayTiming(int ind, double num){
    if (ind<6 and ind >=0){
        Bandeja * temp = bandejas->get(ind);
        temp->cronometro->limite = num;
    }
}

//Funcion temporal (Probablemente despues usemos una que funcione con tiempo real)
int Oven::galletasHorneadas(){
    return cookiesCooked;
}

void Oven::apagarBandejas(int indiceBandeja){
    if (indiceBandeja<6 and indiceBandeja>1){
        bandejas->get(indiceBandeja)->turnOff();
    }
}

void Oven::setTrayStatus(int ind){
    if (0 <= ind && ind <= 5){
        Bandeja * temp = bandejas->get(ind);
        if (temp->state){
            temp->turnOff();
        }else{
            temp->turnOn();
        }
    }
}

int Oven::galletasEnEspera(){
    int wc = bandaEntrada->queue->length; //wc significa waiting cookies//
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

// Retorna un string con info de cada bandeja
string Oven::getTraysInfo(){
    Bandeja * temp = NULL;
    string data = "";

    for (int i = 0; i < bandejas->length; i++){
        temp = bandejas->get(i);

        // Para evitar errores...
        if (temp == NULL) continue;

        data += "Bandeja #" + to_string(i + 1) + "\n";
        data += temp->toString();
    }

    return data;
}
