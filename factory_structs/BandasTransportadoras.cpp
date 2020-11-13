
#include../lists/Queue.h"

struct BandasTransportadoras{
	int maxCapacity;
	int length;
	Queue * queue;
	
	BandasTransportadoras(int _capacity,int _length){
		maxCapacity = _capacity;
		length = _length;
		queue = new Queue();
		
	}
	
};
