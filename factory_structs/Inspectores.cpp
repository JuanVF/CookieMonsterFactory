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

    //Retorna las galletas que pasaron por la revision
    int qualityCookies(int cookiesReceived){
        int trash = cookiesReceived * (rejectionPercentage/100);
        return cookiesReceived - trash;
    }

    //Retorna el numero de galletas que no fueron aceptadas
    int badCookies(int cookiesReceived){
        return cookiesReceived * (rejectionPercentage/100);
    }


};
