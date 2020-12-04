#include <lists/LinkedList.h>
#include <factory_structs/factoryStructs.h>
#include <factory_structs/PlannerPacks.h>

#ifndef TIME_H
#define TIME_H
#include <time.h>
#endif

struct Transportador{
    PlannerPacks * packagesType;
    int currentPacks; // Es la cantidad que esta transportando
    clock_t started;
	
    Transportador(PlannerPacks * package){
        packagesType = package;
        currentPacks = 0;
	}

    void initTime(){
        started = clock();
    }
};
