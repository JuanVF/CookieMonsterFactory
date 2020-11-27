#include <QLabel>
#include "mainwindow.h"
#include <mainwindowdata.h>

// Esta es la animacion de
void * ovenQueueAnimation(void * args){
    QLabel * lbOven = (QLabel *) args;

    QString animations[] = {
        "border-image: url(:/imgs/images/OvenQueue/oven-queue.svg) 0 0 0 0 stretch stretch;",
        "border-image: url(:/imgs/images/OvenQueue/oven-queue2.svg) 0 0 0 0 stretch stretch;",
        "border-image: url(:/imgs/images/OvenQueue/oven-queue3.svg) 0 0 0 0 stretch stretch;",
        "border-image: url(:/imgs/images/OvenQueue/oven-queue4.svg) 0 0 0 0 stretch stretch;",
    };

    while (isTurnedOn){
        if (!isInPause) for (int i = 0; i < 4; i++){
            util->delay(0.2);
            lbOven->setStyleSheet(animations[i]);
        }
    }

    lbOven->setStyleSheet(animations[0]);

    return (void *) 0;
}
