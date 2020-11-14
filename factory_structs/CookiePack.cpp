#include <lists/CircularList.h>
#include <factory_structs/Cookie.h>

// Esto son los diferentes tipos de paquetes que trabaja el proceso de produccion
struct CookiePack{
	int amountCookies;
	string name;
	
    CookiePack(int _amountCookies, string _name){
		amountCookies = _amountCookies;
		name          = _name;
	}
};
