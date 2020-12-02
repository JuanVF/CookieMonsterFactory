#include "view/mainwindow.h"
#include "ui_mainwindow.h"
#include <view/mainwindowdata.h>
#include <view/animations.h>
#include <view/threads.h>
#include <QMutex>

#include <string>

void initComponents(Ui::MainWindow * ui);

Machines machines;
UIThread uiThread;
QMutex app_mutex;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setFixedSize(this->size());

    initComponents(ui);
}

MainWindow::~MainWindow(){
    delete ui;
}

// Inicializa algunos componentes
void initComponents(Ui::MainWindow * ui){
    // Algunos componentes que necesitan los hilos
    LinkedList<QPlainTextEdit *> * textEdits = new LinkedList<QPlainTextEdit *>();

    textEdits->add(ui->lbCarQueue);

    textEdits->add(ui->teCM1Pending);
    textEdits->add(ui->teCM1Processed);

    textEdits->add(ui->teCM2Pending);
    textEdits->add(ui->teCM2Processed);

    textEdits->add(ui->teDMPending);
    textEdits->add(ui->teDMProcessed);

    uiThread.init(textEdits, &app_mutex);
    machines.init(&app_mutex);

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

// Funcion que se va a encargar de encender todas las maquinas
void setup(Ui::MainWindow * ui){
    machines.start();
    uiThread.start();
}

void MainWindow::on_btnTurnOn_clicked(){
    if (isTurnedOn){
        turnOffAnimation(ui->btnTurnOn, ui->btnPause, ui->lbStatus);
        isInPause = false;
    }else if (!isInPause){
        turnOnAnimation(ui->btnTurnOn, ui->lbStatus);
        setup(ui);
    }

    isTurnedOn = !isTurnedOn;
}

void MainWindow::on_btnPause_clicked(){
    if (isTurnedOn){
        if (isInPause){
            pauseOffAnimation(ui->btnPause, ui->lbStatus);
        }else{
            pauseOnAnimation(ui->btnPause, ui->lbStatus);
        }

        isInPause = !isInPause;
    }
}

// Retorna un string con el texto de un lineedit
string getText(QLineEdit * le){
    return le->text().toStdString();
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

    string strAmount = to_string(planner->packs->length);

    ui->lbPlannerPackAmount->setText(strAmount.c_str());
    ui->cbPlannerPacks->addItems(list);
}

// OnClicks de las maquinas
void MainWindow::on_btnPlanner_clicked(){
    ui->lePlannerDough->setText(to_string(planner->recipe->amountDough).c_str());
    ui->lePlannerChoc->setText(to_string(planner->recipe->amountChocolate).c_str());

    ui->swProperties->setCurrentIndex(0);
}

void MainWindow::on_btnWarehouse_clicked(){
    ui->leWHCapacity->setText(to_string(warehouse->car->capacity).c_str());
    ui->leWHDelay->setText(to_string(warehouse->car->delay).c_str());
    ui->swProperties->setCurrentIndex(1);
}

void MainWindow::on_btnChocMix2_clicked(){
    ui->leCM2Min->setText(to_string(chocolateMixer2->min).c_str());
    ui->leCM2Max->setText(to_string(chocolateMixer2->max).c_str());
    ui->leCM2Prod->setText(to_string(chocolateMixer2->capacity).c_str());
    ui->leCM2Delay->setText(to_string(chocolateMixer2->delay).c_str());
    ui->swProperties->setCurrentIndex(4);
}

void MainWindow::on_btnDoughMix_clicked(){
    ui->leCM1Min->setText(to_string(chocolateMixer1->min).c_str());
    ui->leCM1Max->setText(to_string(chocolateMixer1->max).c_str());
    ui->leCM1Prod->setText(to_string(chocolateMixer1->capacity).c_str());
    ui->leCM1Delay->setText(to_string(chocolateMixer1->delay).c_str());
    ui->swProperties->setCurrentIndex(3);
}

void MainWindow::on_btnChocMix1_clicked(){
    ui->leDMMin->setText(to_string(doughMixer->min).c_str());
    ui->leDMMax->setText(to_string(doughMixer->max).c_str());
    ui->leDMProd->setText(to_string(doughMixer->capacity).c_str());
    ui->leDMDelay->setText(to_string(doughMixer->delay).c_str());
    ui->swProperties->setCurrentIndex(2);
}

void MainWindow::on_btnAssembly_clicked(){
    ui->leAsmChoc->setText(to_string(assembler->chocolate->maxCapacity).c_str());
    ui->leAsmDough->setText(to_string(assembler->dough->maxCapacity).c_str());
    ui->leAsmProd->setText(to_string(assembler->capacity).c_str());
    ui->leAsmDelay->setText(to_string(assembler->delay).c_str());
    ui->swProperties->setCurrentIndex(5);

}

void MainWindow::on_btnOven_clicked(){
    ui->swProperties->setCurrentIndex(6);
}

void MainWindow::on_btnPacker_clicked(){
    ui->swProperties->setCurrentIndex(7);
}

// Setteo de los parametros de las maquinas

/*
 *  MAQUINA: Planner - es una persona pero bueh
 * */
void MainWindow::on_btnPlannerApply_clicked(){
    string strChoc = getText(ui->lePlannerChoc);
    string strDough = getText(ui->lePlannerDough);

    QMessageBox msgBox;

    if (strChoc == ""){
        msgBox.setText("El input de la cantidad de chocolate esta vacio...");
    } else if (strDough == ""){
        msgBox.setText("El input de la cantidad de masa esta vacio...");
    } else {
        double amountChocolate = util->toDouble(strChoc);
        double amountDough = util->toDouble(strDough);

        planner->recipe->setData(amountDough, amountChocolate);

        msgBox.setText("Cambios hechos!");
    }
    msgBox.exec();
}

void MainWindow::on_btnPlannerAdd_clicked(){
    string name = getText(ui->lePlannerName);
    int amount = 0;

    QMessageBox msgBox;

    if (name == ""){
        msgBox.setText("Introduzca el nombre del paquete!");
    } else if (getText(ui->lePlannerAmount) == ""){
        msgBox.setText("Introduzca la cantidad de galletas!");
    } else {
        amount = util->toInt(getText(ui->lePlannerAmount));
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
    string name = getText(ui->lePlannerName);

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
    string amountTxt = getText(ui->lePlannerDel);
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

            planner->plan();
            ui->lbPlannerCookies->setText(to_string(planner->getTotalCookies()).c_str());
        }
    }

    msgBox.exec();
}

void MainWindow::on_btnDelPack_clicked(){
    string amountTxt = getText(ui->lePlannerDel);
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

            planner->plan();
            ui->lbPlannerCookies->setText(to_string(planner->getTotalCookies()).c_str());
        }
    }

    msgBox.exec();
}

/*
 *  MAQUINA: WareHouse - Almacen
 * */
void MainWindow::on_btnWHApply_clicked(){
    string strCapacity = getText(ui->leWHCapacity);
    string strDelay = getText(ui->leWHDelay);

    QMessageBox msgBox;

    if (strCapacity == ""){
        msgBox.setText("El input de capacidad esta vacio...");
    } else if (strDelay == ""){
        msgBox.setText("El input del tiempo de entrega esta vacio...");
    } else {
        int capacity = util->toInt(strCapacity);
        float delay = util->toDouble(strDelay);

        warehouse->setData(delay, capacity);

        msgBox.setText("Cambios aplicados...");
    }

    msgBox.exec();
}

/*
 *  MAQUINAS: Mezcladoras
 * */

// Esta funcion es para todas las maquinas mezcladoras pues son
// Exactamente la misma, sirve para validarlas y settearlas
void setMixer(MixerMachine * mixer, QLineEdit * leMin, QLineEdit * leMax, QLineEdit * leDelay, QLineEdit * leProd){
    string strMin = getText(leMin);
    string strMax = getText(leMax);
    string strDelay = getText(leDelay);
    string strProd = getText(leProd);

    QMessageBox msgBox;

    if (strMin == ""){
        msgBox.setText("El input del minimo esta vacio...");
    } else if (strMax == ""){
        msgBox.setText("El input del maximo esta vacio...");
    } else if (strDelay == ""){
        msgBox.setText("El input del tiempo de entrega esta vacio...");
    } else if (strProd == ""){
        msgBox.setText("El input de producción esta vacio...");
    } else {
        int min = util->toInt(strMin);
        int max = util->toInt(strMax);
        double delay = util->toDouble(strDelay);
        double prod = util->toDouble(strProd);

        mixer->setData(min, max, prod, delay);
        msgBox.setText("Cambios aplicados");
    }

    msgBox.exec();
}

void MainWindow::on_btnCM2Apply_clicked(){
    setMixer(chocolateMixer2, ui->leCM2Min, ui->leCM2Max, ui->leCM2Delay, ui->leCM2Prod);
}

void MainWindow::on_btnDMApply_clicked(){
    setMixer(doughMixer, ui->leDMMin, ui->leDMMax, ui->leDMDelay, ui->leDMProd);
}

void MainWindow::on_btnCM1Apply_clicked(){
    setMixer(chocolateMixer1, ui->leCM1Min, ui->leCM1Max, ui->leCM1Delay, ui->leCM1Prod);
}

/*
 *  MAQUINA: Ensambladora
 * */

void MainWindow::on_btnAsmApply_clicked(){
    string strChoc = getText(ui->leAsmChoc);
    string strDelay = getText(ui->leAsmDelay);
    string strDough = getText(ui->leAsmDough);
    string strProd = getText(ui->leAsmProd);

    QMessageBox msgBox;

    if (strChoc == ""){
        msgBox.setText("El input de la banda chocolate esta vacio...");
    } else if (strDelay == ""){
        msgBox.setText("El input del tiempo de producción esta vacio...");
    } else if (strDough == ""){
        msgBox.setText("El input de la banda de masa esta vacio...");
    } else if (strProd == ""){
        msgBox.setText("El input de la cantidad a producir esta vacio...");
    } else {
        double delay = util->toDouble(strDelay);
        int prod = util->toInt(strProd);
        int choc = util->toInt(strChoc);
        int dough = util->toInt(strDough);

        assembler->setData(dough, choc, delay, prod);

        msgBox.setText("Cambios aplicados!");
    }

    msgBox.exec();
}
