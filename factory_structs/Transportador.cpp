#include <factory_structs/CookiePack.h>
#include <lists/LinkedList.h>

struct Transportador{
	LinkedList<CookiePack*> * packagesType;
	
	Transportador(){
		packagesType = new  LinkedList<CookiePack*>();
	}
	
};
