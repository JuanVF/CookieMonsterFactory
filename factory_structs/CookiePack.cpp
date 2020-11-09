#include "../lists/CircularList.h"
#include "Cookie.h"

struct CookiePack{
	CircularList<Cookie*> * cookies;
	int amountCookies;
	string name;
	
	CookiePack(int _amountCookies, string _name){
		cookies       = new CircularList<Cookie*>();
		amountCookies = _amountCookies;
		name          = _name;
	}
};
