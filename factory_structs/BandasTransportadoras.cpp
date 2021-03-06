#include <lists/Queue.h>

template <typename Data>
struct BandasTransportadoras{
	int maxCapacity;
	int length;

    bool isTurnedOn;

    Queue<Data> * queue;
	
    BandasTransportadoras(int _capacity){
        maxCapacity = _capacity;

        queue = new Queue<Data>();

        isTurnedOn = true;
	}
	
    // Agrega un elemento a la cola de la banda
    // Retorna falso si no se pudo agregar o si llego a capacidad maxima
    bool add(Data _data){
        if (!isTurnedOn || isOverCapacity()) return false;

        queue->enqueue(_data);

        if (isOverCapacity()) isTurnedOn = false;

        return !isOverCapacity();
    }

    // Obtiene el primer elemento de la cola
    // Retorna nulo si no tiene ninguno o esta apagada
    Data get(){
        if (!isTurnedOn) return (Data) NULL;

        return queue->dequeue();
    }

    // Determina si la banda ya esta a sobre capacidad
    bool isOverCapacity(){
        return queue->length >= maxCapacity;
    }

    //Agrega los ints 1 por 1, para que cuente cada galleta y no cuente un numero grande como un solo elemento
    int agregarIndividual (int numero){
        while (numero>0){
            add(1);
            numero--;
            if (isOverCapacity()){
                return 1;
            }
        }
        return 0;

    }
};
