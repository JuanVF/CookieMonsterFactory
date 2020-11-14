#include <lists/Queue.h>

template <typename Data>
struct BandasTransportadoras{
	int maxCapacity;
	int length;
    Queue<Data> * queue;
	
    BandasTransportadoras(int _capacity, int _length){
		maxCapacity = _capacity;
		length = _length;
        queue = new Queue<Data>();
	}
	
};
