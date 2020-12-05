#include <QRandomGenerator>
#include <lists/LinkedList.h>
using namespace std;


struct Inspectores{
    LinkedList<int> * registro;
    int random = QRandomGenerator::global()->bounded(15);

    Inspectores(){
        registro = new LinkedList<int>();
        random = QRandomGenerator::global()->bounded(15);
	}

    //Retorna las galletas que pasaron por la revision
    int qualityCookies(int cookiesReceived){
        int trash = cookiesReceived * (random/100);
        return cookiesReceived - trash;
    }

    //Retorna el numero de galletas que no fueron aceptadas
    int badCookies(int cookiesReceived){
        int bc =cookiesReceived * (random/100);
        //string x = to_string(bc);
        registro->addFirst(bc);
        return bc;
    }

};
