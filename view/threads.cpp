#include "view/mainwindow.h"
#include <view/mainwindowdata.h>
#include <QThread>

void setMachines(bool status){
    warehouse->isRunning = status;
    chocolateMixer1->isRunning = status;
    chocolateMixer2->isRunning = status;
    doughMixer->isRunning = status;
    assembler->isRunning = status;
}

// Aqui van a ir todos los hilos de las maquinas
void * machines_thread_run(void * arg){
    setMachines(true);

    while(isTurnedOn) if (!isInPause){
        warehouse->checking();
        chocolateMixer1->mix();
        chocolateMixer2->mix();
        doughMixer->mix();

        util->delay(1/60);
    }

    setMachines(false);
}

