#ifndef IOSSTREAM
#define IOSSTREAM
#include <iostream>
using namespace std;
#endif
#include <lists/LinkedList.h>

struct Inspectores{
	double rejectionPercentage;
    LinkedList<string> * registro;
	
	Inspectores(double _percentage){
        rejectionPercentage = _percentage;
        registro = new LinkedList<string>();
	}
};
