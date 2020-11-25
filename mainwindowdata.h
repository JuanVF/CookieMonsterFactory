#ifndef MAINWINDOWDATA_H
#define MAINWINDOWDATA_H

#include <lists/dataStructures.h>
#include <machines/machines.h>
#include <factory_structs/factoryStructs.h>
#include <enums.h>

#include <machines/Planner.h>
#include <machines/Warehouse.h>
#include <machines/Assembler.h>
#include <machines/MixerMachine.h>

#include <Util.h>
#include <pthread.h>

// Definicion de variables
bool isTurnedOn = false;
bool isInPause = false;
Util * util = new Util();
pthread_t animation_thread;

Planner * planner = new Planner();
WareHouse * warehouse = new WareHouse();
Assembler * assembler = new Assembler();

MixerMachine * chocolateMixer1 = new MixerMachine(warehouse, assembler, Chocolate);
MixerMachine * chocolateMixer2 = new MixerMachine(warehouse, assembler, Chocolate);
MixerMachine * doughMixer = new MixerMachine(warehouse, assembler, Dough);

#endif
