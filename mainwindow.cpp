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

    // Estos son validaciones para evitar que el usuario
    // Meta letras donde solo van numeros
    // Se usan Regular Expressions para hacer las validaciones
    ui->leAsmDelay->setValidator(floatVal);
    ui->leAsmChoc->setValidator(intVal);
    ui->leAsmDough->setValidator(intVal);
    ui->leAsmProd->setValidator(intVal);

    ui->lePlannerChoc->setValidator(floatVal);
    ui->lePlannerDel->setValidator(intVal);
    ui->lePlannerDough->setValidator(floatVal);

    ui->leWHCapacity->setValidator(intVal);
    ui->leWHDelay->setValidator(floatVal);

    ui->leCM1Delay->setValidator(floatVal);
    ui->leCM1Max->setValidator(intVal);
    ui->leCM1Min->setValidator(intVal);
    ui->leCM1Prod->setValidator(floatVal);

    ui->leCM2Delay->setValidator(floatVal);
    ui->leCM2Max->setValidator(intVal);
    ui->leCM2Min->setValidator(intVal);
    ui->leCM2Prod->setValidator(floatVal);

    ui->leDMDelay->setValidator(floatVal);
    ui->leDMMax->setValidator(intVal);
    ui->leDMMin->setValidator(intVal);
    ui->leDMProd->setValidator(floatVal);
}

MainWindow::~MainWindow(){
    delete ui;
}

// Funcion que se va a encargar de encender todas las maquinas
void setup(QLabel * lbChocolateQueue){
    pthread_create(&animation_thread, NULL, ovenQueueAnimation, (void *) lbChocolateQueue);
}

void MainWindow::on_btnTurnOn_clicked(){
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

void MainWindow::on_btnPause_clicked(){
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

// OnClicks de las maquinas
void MainWindow::on_btnPlanner_clicked(){
    ui->swProperties->setCurrentIndex(0);
}

void MainWindow::on_btnWarehouse_clicked(){
    ui->swProperties->setCurrentIndex(1);
}

void MainWindow::on_btnChocMix2_clicked(){
    ui->swProperties->setCurrentIndex(2);
}

void MainWindow::on_btnDoughMix_clicked(){
    ui->swProperties->setCurrentIndex(3);
}

void MainWindow::on_btnChocMix1_clicked(){
    ui->swProperties->setCurrentIndex(4);
}

void MainWindow::on_btnAssembly_clicked(){
    ui->swProperties->setCurrentIndex(5);
}
