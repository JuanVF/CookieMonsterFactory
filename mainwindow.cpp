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
    ui->lePlannerAmount->setValidator(intVal);
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

// Actualiza los datos del combo box del planner
void setPlannerComboBox(Ui::MainWindow *ui){
    QStringList list = QStringList();

    ui->cbPlannerPacks->clear();

    for (int i = 0; i < planner->packs->length; i++){
        PlannerPacks * pack = planner->packs->get(i);
        string name = pack->getName();

        list.append(QString("").append(name.c_str()));
    }

    cout << endl;

    ui->cbPlannerPacks->addItems(list);
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

// Setteo de los parametros de las maquinas

/*
 *  MAQUINA: Planner -es una persona pero bueh
 * */
void MainWindow::on_btnPlannerApply_clicked(){
    double amountChocolate = util->toDouble(ui->lePlannerChoc->text().toStdString());
    double amountDough = util->toDouble(ui->lePlannerDough->text().toStdString());

    planner->recipe->setData(amountDough, amountChocolate);

    QMessageBox msgBox;

    msgBox.setText("Cambios hechos!");
    msgBox.exec();
}

void MainWindow::on_btnPlannerAdd_clicked(){
    string name = ui->lePlannerName->text().toStdString();
    int amount = 0;

    QMessageBox msgBox;

    if (name == ""){
        msgBox.setText("Introduzca el nombre del paquetes!");
    } else if (ui->lePlannerAmount->text().toStdString() == ""){
        msgBox.setText("Introduzca la cantidad de galletas!");
    } else {
        amount = util->toInt(ui->lePlannerAmount->text().toStdString());
        bool added = planner->addPack(amount, name);

        if (added){
            msgBox.setText("Cambios hechos!");

            ui->lePlannerAmount->setText(QString(""));
            ui->lePlannerName->setText(QString(""));

            setPlannerComboBox(ui);
        } else {
            msgBox.setText("El paquete ya existe!");
        }
    }

    msgBox.exec();
}

void MainWindow::on_btnPlannerDel_clicked(){
    string name = ui->lePlannerName->text().toStdString();

    QMessageBox msgBox;

    if (name == ""){
        msgBox.setText("Introduzca el nombre del paquete!");

    } else{
        bool deleted = planner->removePack(name);

        if (deleted){
            msgBox.setText("Paquete eliminado!");
            ui->lePlannerName->setText("");
            setPlannerComboBox(ui);
        }else {
            msgBox.setText("El paquete no existe...");
        }
    }

    msgBox.exec();
}

void MainWindow::on_btnAddPack_clicked(){
    string amountTxt = ui->lePlannerDel->text().toStdString();
    string name = ui->cbPlannerPacks->currentText().toStdString();

    QMessageBox msgBox;

    if (amountTxt == ""){
        msgBox.setText("Ingrese una cantidad a agregar...");
    } else if (name == ""){
        msgBox.setText("Agregue paquetes al planeador...");
    }else{
        int amount = util->toInt(amountTxt);

        PlannerPacks * pack = planner->findPack(name);

        if (pack == NULL){
            // En teoria nunca deberia llegar a esta parte...
            // Pero esta bien tener la validacion en caso de bugs...
            msgBox.setText("El paquete no existe...");
        } else{
            pack->addPacks(amount);
            ui->lePlannerDel->setText("");
            msgBox.setText("Cantidad de paquetes agregados!");
        }
    }

    msgBox.exec();
}

void MainWindow::on_btnDelPack_clicked(){
    string amountTxt = ui->lePlannerDel->text().toStdString();
    string name = ui->cbPlannerPacks->currentText().toStdString();

    QMessageBox msgBox;

    if (amountTxt == ""){
        msgBox.setText("Ingrese una cantidad a agregar...");
    } else if (name == ""){
        msgBox.setText("Agregue paquetes al planeador...");
    }else{
        int amount = util->toInt(amountTxt);

        PlannerPacks * pack = planner->findPack(name);

        if (pack == NULL){
            // En teoria nunca deberia llegar a esta parte...
            // Pero esta bien tener la validacion en caso de bugs...
            msgBox.setText("El paquete no existe...");
        } else{
            pack->removePacks(amount);
            ui->lePlannerDel->setText("");
            msgBox.setText("Cantidad de paquetes removidos!");
        }
    }

    msgBox.exec();
}
