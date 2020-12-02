#include <factory_structs/CookiePack.h>
#include <factory_structs/PlannerPacks.h>
#include <lists/LinkedList.h>

struct Transportador{
    LinkedList<PlannerPacks*> * packagesType;
	
	Transportador(){
        packagesType = new  LinkedList<PlannerPacks*>();
	}
	
};
