#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <mainwindowdata.h>
#include <view/animations.h>

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
