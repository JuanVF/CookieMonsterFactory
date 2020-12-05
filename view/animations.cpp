#include <QLabel>
#include <QPushButton>

#include "view/mainwindow.h"
#include <view/mainwindowdata.h>

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

void turnOffAnimation(QPushButton * btnTurnOn, QPushButton * btnPause, QLabel * lbStatus){
    btnTurnOn->setStyleSheet(QString("border-image: url(:/imgs/images/power-button.svg) 0 0 0 0 stretch stretch;"));
    btnPause->setStyleSheet(QString("border-image: url(:/imgs/images/pause-button-on.svg)  0 0 0 0 stretch stretch;"));
    lbStatus->setText(QString("Apagada"));
}

void turnOnAnimation(QPushButton * btnTurnOn, QLabel * lbStatus){
    btnTurnOn->setStyleSheet(QString("border-image: url(:/imgs/images/power.svg) 0 0 0 0 stretch stretch;"));
    lbStatus->setText(QString("Encendida"));
}

void pauseOffAnimation(QPushButton * btnPause, QLabel * lbStatus){
    btnPause->setStyleSheet(QString("border-image: url(:/imgs/images/pause-button-off.svg)  0 0 0 0 stretch stretch;"));
    lbStatus->setText(QString("En pausa"));
}

void pauseOnAnimation(QPushButton * btnPause, QLabel * lbStatus){
    btnPause->setStyleSheet(QString("border-image: url(:/imgs/images/pause-button-on.svg)  0 0 0 0 stretch stretch;"));
    lbStatus->setText(QString("Encendida"));
}
