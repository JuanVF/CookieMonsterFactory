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
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QMessageBox>

// Definicion de variables

// Estas variables se encargan de manejar
// todos los estados de las maquinas dependiendo si esta encendida o pausada
bool isTurnedOn = false;
bool isInPause = false;

Util * util = new Util();

pthread_t animation_thread; // Este es el hilo en el corren las animaciones
pthread_t ui_thread; // Este hilo es para los cambios en la UI
pthread_t machines_thread; // Este hilo es para los cambios en la UI

// Aqui se inicializan las maquinas
Planner * planner = new Planner();
WareHouse * warehouse = new WareHouse();
Assembler * assembler = new Assembler();

MixerMachine * chocolateMixer1 = new MixerMachine(warehouse, assembler, Chocolate, "Mezcladora de chocolate #1");
MixerMachine * chocolateMixer2 = new MixerMachine(warehouse, assembler, Chocolate, "Mezcladora de chocolate #2");
MixerMachine * doughMixer = new MixerMachine(warehouse, assembler, Dough, "Mezcladora de masa");

// Estos son las que se encargan de hacer esas validaciones
// con las Regular Expression
// El string con simbolos raros es el RegEx
QRegularExpressionValidator * floatVal = new QRegularExpressionValidator(QRegularExpression("\\d+(\\.)?(\\d{1,5})?"), NULL);
QRegularExpressionValidator * intVal = new QRegularExpressionValidator(QRegularExpression("\\d+"), NULL);
#endif
