#include "view/mainwindow.h"
#include <view/mainwindowdata.h>

// Aqui van a ir todos los hilos de las maquinas

// Hilo para el warehouse
void * wh_thread_run(void * args){
    warehouse->checking();

    return (void *) 0;
}
void * cm1_thread_run(void * args){
    chocolateMixer1->mix();

    return (void *) 0;
}
void * cm2_thread_run(void * args){
    chocolateMixer2->mix();

    return (void *) 0;
}
void * dm_thread_run(void * args){
    doughMixer->mix();

    return (void *) 0;
}
