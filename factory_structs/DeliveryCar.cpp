struct DeliveryCar{
	int amountChocolate;
	int amountDough;
	int capacity;
	double delay;
	
	// Constructor
	DeliveryCar(int _capacity, double _delay){
		capacity = _capacity;
		delay = _delay;
		amountChocolate = 0;
		amountDough = 0;
	}
};
