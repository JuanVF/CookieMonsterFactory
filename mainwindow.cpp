#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifndef IOSSTREAM
#define IOSSTREAM
#include <iostream>
using namespace std;
#endif

bool isTurnedOn = false;
bool isInPause = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
}

// Funcion que se va a encargar de encender todas las maquinas
void setup(){

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
    }

    setup();

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
