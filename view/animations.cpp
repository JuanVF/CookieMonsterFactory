#include <QLabel>
#include <QPushButton>

#include "view/mainwindow.h"
#include <view/mainwindowdata.h>

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
