#ifndef IOSSTREAM
#define IOSSTREAM
#include <iostream>
#include "../lists/LinkedList.h"
using namespace std;
#endif

struct Inspectores{
	double rejectionPercentage;
    LinkedList<string> * registro;
	
	Inspectores(double _percentage){
        rejectionPercentage = _percentage;
        registro = new LinkedList<string>();
	}
};
