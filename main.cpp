#include "mainwindow.h"
#include <QApplication>

#include <lists/dataStructures.h>
#include <machines/machines.h>
#include <factory_structs/factoryStructs.h>

#include <machines/Planner.h>
#include <machines/Warehouse.h>
#include <machines/MixerMachine.h>

int main(int argc, char *argv[])
{
    Planner * planner = new Planner(10, 10);
    WareHouse * ware = new WareHouse(100, 1);
    MixerMachine * mixer = new MixerMachine(ware, 1,1,1,1,1);

    return 0;
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();
}
