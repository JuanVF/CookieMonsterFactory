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
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
