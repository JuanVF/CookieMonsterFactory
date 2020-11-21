#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <pthread.h>
#include <Util.h>

#ifndef IOSSTREAM
#define IOSSTREAM
#include <iostream>
using namespace std;
#endif

bool isTurnedOn = false;
bool isInPause = false;

pthread_t animation_thread;
Util * util = new Util();

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
}

void * ovenQueueAnimation(void * args){
    QLabel * lbOven = (QLabel *) args;

    QString animations[] = {
        "border-image: url(:/imgs/images/OvenQueue/oven-queue.svg) 0 0 0 0 stretch stretch;",
        "border-image: url(:/imgs/images/OvenQueue/oven-queue2.svg) 0 0 0 0 stretch stretch;",
        "border-image: url(:/imgs/images/OvenQueue/oven-queue3.svg) 0 0 0 0 stretch stretch;",
        "border-image: url(:/imgs/images/OvenQueue/oven-queue4.svg) 0 0 0 0 stretch stretch;",
    };

    while (isTurnedOn && !isInPause){
        for (int i = 0; i < 4; i++){
            util->delay(1);
            lbOven->setStyleSheet(animations[i]);
        }
    }

    lbOven->setStyleSheet(animations[0]);
}

// Funcion que se va a encargar de encender todas las maquinas
void setup(QLabel * lbChocolateQueue){
    pthread_create(&animation_thread, NULL, ovenQueueAnimation, (void *) lbChocolateQueue);
}

void MainWindow::on_btnTurnOn_clicked()
{
    if (isTurnedOn){
        ui->btnTurnOn->setStyleSheet(QString("border-image: url(:/imgs/images/power-button.svg) 0 0 0 0 stretch stretch;"));
        ui->btnPause->setStyleSheet(QString("border-image: url(:/imgs/images/pause-button-on.svg)  0 0 0 0 stretch stretch;"));
        ui->lbStatus->setText(QString("Apagada"));
        isInPause = false;
    }else if (!isInPause){
        ui->btnTurnOn->setStyleSheet(QString("border-image: url(:/imgs/images/power.svg) 0 0 0 0 stretch stretch;"));
        ui->lbStatus->setText(QString("Encendida"));

        setup(ui->lbChocolateQueue);
    }

    isTurnedOn = !isTurnedOn;
}

void MainWindow::on_btnPause_clicked()
{
    if (isTurnedOn){
        if (isInPause){
            ui->btnPause->setStyleSheet(QString("border-image: url(:/imgs/images/pause-button-on.svg)  0 0 0 0 stretch stretch;"));
            ui->lbStatus->setText(QString("Encendida"));
        }else{
            ui->btnPause->setStyleSheet(QString("border-image: url(:/imgs/images/pause-button-off.svg)  0 0 0 0 stretch stretch;"));
            ui->lbStatus->setText(QString("En pausa"));
        }

        isInPause = !isInPause;
    }
}
