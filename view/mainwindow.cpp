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
    LinkedList<QLabel *> * labels = new LinkedList<QLabel *>();
    LinkedList<QPushButton *> * buttons = new LinkedList<QPushButton *>();

    textEdits->add(ui->lbCarQueue);

    textEdits->add(ui->teCM1Pending);
    textEdits->add(ui->teCM1Processed);

    textEdits->add(ui->teCM2Pending);
    textEdits->add(ui->teCM2Processed);

    textEdits->add(ui->teDMPending);
    textEdits->add(ui->teDMProcessed);

    labels->add(ui->lbAsmAssembled);

    textEdits->add(ui->teAsmChocolate);
    textEdits->add(ui->teAsmDough);

    labels->add(ui->lbCM1Processed);
    labels->add(ui->lbCM2Processed);
    labels->add(ui->lbDMProcessed);

    textEdits->add(ui->teOvenTrayInfo);
    labels->add(ui->lbOvenCooking);
    labels->add(ui->lbOvenMaxCookies);
    labels->add(ui->lbOvenWaiting);

    textEdits->add(ui->tePackerPacked);
    textEdits->add(ui->teTrans);

    labels->add(ui->lbInspDel1);
    labels->add(ui->lbInspDel2);

    textEdits->add(ui->lbDepositPacks);
    labels->add(ui->lbDepositTotal);

    buttons->add(ui->btnWHTurnOn);

    buttons->add(ui->btnCM1TurnON);
    buttons->add(ui->btnCM2TurnON);
    buttons->add(ui->btnDMTurnON);

    buttons->add(ui->btnAsmTurnON);
    buttons->add(ui->btnOvenTurnOn);

    buttons->add(ui->btnTransTurnOn);
    buttons->add(ui->btnPackerTurnOn);

    uiThread.init(textEdits, labels, buttons, &app_mutex);
    machines.init(&app_mutex);

    // Estos son validaciones para evitar que el usuario no
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

    ui->leOvenBand1->setValidator(intVal);
    ui->leOvenBand2->setValidator(intVal);
    ui->leOvenBand3->setValidator(intVal);
    ui->leOvenBand4->setValidator(intVal);
    ui->leOvenBand5->setValidator(intVal);
    ui->leOvenBand6->setValidator(intVal);

    ui->leOvenBand1Delay->setValidator(floatVal);
    ui->leOvenBand2Delay->setValidator(floatVal);
    ui->leOvenBand3Delay->setValidator(floatVal);
    ui->leOvenBand4Delay->setValidator(floatVal);
    ui->leOvenBand5Delay->setValidator(floatVal);
    ui->leOvenBand6Delay->setValidator(floatVal);

    ui->leOvenCapacity->setValidator(intVal);
    ui->leOvenBandCapacity->setValidator(intVal);

    ui->lePackerCapacity->setValidator(intVal);
    ui->lePackerDelay->setValidator(floatVal);
    ui->lePackerMaxBand->setValidator(intVal);

    ui->leTransCapacity->setValidator(intVal);
    ui->leTransDelay->setValidator(floatVal);
}

// Funcion que se va a encargar de encender todas las maquinas
void setup(){
    machines.start();
    uiThread.start();
}

void MainWindow::on_btnTurnOn_clicked(){
    if (machines.canMachinesStart()){
        if (isTurnedOn){
            turnOffAnimation(ui->btnTurnOn, ui->btnPause, ui->lbStatus);
            isInPause = false;
        }else if (!isInPause){
            turnOnAnimation(ui->btnTurnOn, ui->lbStatus);
            setup();
        }

        isTurnedOn = !isTurnedOn;
    }
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

void MainWindow::on_btnTrans_clicked(){
    ui->swProperties->setCurrentIndex(8);
}

void MainWindow::on_btnInspector_clicked(){
    ui->swProperties->setCurrentIndex(9);
}

void MainWindow::on_btnDeposit_clicked(){
    ui->swProperties->setCurrentIndex(10);
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

/*
 *  MAQUINA: Horno
 * */

void MainWindow::on_btnOvenApply_clicked(){
    LinkedList<string> * bands = new LinkedList<string>();
    LinkedList<string> * bandsDelay = new LinkedList<string>();

    bool areBandsEmpty = false;
    bool areBandsDelayEmpty = false;

    string ovenCapacity = getText(ui->leOvenCapacity);
    string ovenBandCapacity = getText(ui->leOvenBandCapacity);

    bands->add(getText(ui->leOvenBand1));
    bandsDelay->add(getText(ui->leOvenBand1Delay));

    bands->add(getText(ui->leOvenBand2));
    bandsDelay->add(getText(ui->leOvenBand2Delay));

    bands->add(getText(ui->leOvenBand3));
    bandsDelay->add(getText(ui->leOvenBand3Delay));

    bands->add(getText(ui->leOvenBand4));
    bandsDelay->add(getText(ui->leOvenBand4Delay));

    bands->add(getText(ui->leOvenBand5));
    bandsDelay->add(getText(ui->leOvenBand5Delay));

    bands->add(getText(ui->leOvenBand6));
    bandsDelay->add(getText(ui->leOvenBand6Delay));

    // Verificamos que no haya alguna vacia...
    for (int i = 0; i < bands->length; i++){
        areBandsEmpty = bands->get(i) == "";
        areBandsDelayEmpty = bandsDelay->get(i) == "";

        if (areBandsEmpty && areBandsDelayEmpty) break;
    }

    QMessageBox msgBox;

    if (ovenCapacity == ""){
        msgBox.setText("El input de la capacidad esta vacio...");

    } else if (ovenBandCapacity == ""){
        msgBox.setText("El input de la capacidad de la banda esta vacio...");

    } else if (areBandsEmpty){
        msgBox.setText("Algun input de la bandeja esta vacio...");

    } else if (areBandsDelayEmpty){
        msgBox.setText("Algun input del delay de la bandeja esta vacio...");

    } else {
        LinkedList<int> * bandsInt = new LinkedList<int>();
        LinkedList<float> * bandsDelayFloat = new LinkedList<float>();

        int capacity = util->toInt(ovenCapacity);
        int bandCapacity = util->toInt(ovenBandCapacity);

        for (int i = 0; i < bands->length; i++){
            bandsInt->add(util->toInt(bands->get(i)));
            bandsDelayFloat->add(util->toDouble(bandsDelay->get(i)));
        }

        cout << "hi" << endl;
        oven->init(capacity, bandCapacity, bandsDelayFloat, bandsInt);

        msgBox.setText("Cambios aplicados!");
    }

    msgBox.exec();
}

/*
 *  MAQUINA: Empacadora
 * */

void MainWindow::on_btnPackerApply_clicked(){
    string capacity = getText(ui->lePackerCapacity);
    string delay = getText(ui->lePackerDelay);
    string bandMax = getText(ui->lePackerMaxBand);

    QMessageBox msgBox;

    if (capacity == ""){
        msgBox.setText("El input de la capacidad esta vacio...");

    } else if (delay == ""){
        msgBox.setText("El input del delay esta vacio...");

    } else if (bandMax == ""){
        msgBox.setText("El input de la capacidad de la banda esta vacio...");

    } else {
        int intCapacity = util->toInt(capacity);
        float intDelay = util->toDouble(delay);
        int intBandMax = util->toInt(bandMax);

        packer->init(intBandMax, intCapacity, intDelay);

        msgBox.setText("Cambios aplicados!");
    }

    msgBox.exec();
}

// Boton de apply de los transportadores
void MainWindow::on_btnTranApply_clicked(){
    string strCapacity = getText(ui->leTransCapacity);
    string strDelay = getText(ui->leTransDelay);

    QMessageBox msgBox;

    if (strDelay == ""){
        msgBox.setText("El input del delay esta vacio...");

    } else if (strCapacity == ""){
        msgBox.setText("El input de la capacidad esta vacio...");

    } else {
        int capacity = util->toInt(strCapacity);
        float delay = util->toDouble(strDelay);

        trans->setData(capacity, delay);

        msgBox.setText("Cambios aplicados!");
    }

    msgBox.exec();
}

// Boton de apply de los inspectores
void MainWindow::on_btnInspApply_clicked(){
    string strProb1 = getText(ui->leInspProb1);
    string strProb2 = getText(ui->leInspProb2);

    QMessageBox msgBox;

    if (strProb1 == ""){
        msgBox.setText("La probabilidad del inspector 1 esta vacia...");

    } else if (strProb2 == ""){
        msgBox.setText("La probabilidad del inspector 2 esta vacia...");

    } else{
        float prob1 = util->toDouble(strProb1);
        float prob2 = util->toDouble(strProb2);

        oven->initInspectores(prob1, prob2);

        msgBox.setText("Cambios aplicados!");
    }

    msgBox.exec();
}

void setTray(QPushButton * btn, int index){
    oven->setTrayStatus(index);

    setStatusButton(btn, oven->bandejas->get(index)->state);
}

// Eventos de encender las bandejas
void MainWindow::on_btnTurnTray1_clicked(){
    // Esta siempre debe estar encendida
}

void MainWindow::on_btnTurnTray2_clicked(){
    // Esta siempre debe estar encendida
}

void MainWindow::on_btnTurnTray3_clicked(){
    if (app_mutex.tryLock()){
        setTray(ui->btnTurnTray3, 2);
        app_mutex.unlock();
    }
}

void MainWindow::on_btnTurnTray4_clicked(){
    if (app_mutex.tryLock()){
        setTray(ui->btnTurnTray4, 3);
        app_mutex.unlock();
    }

}

void MainWindow::on_btnTurnTray5_clicked(){
    if (app_mutex.tryLock()){
        setTray(ui->btnTurnTray5, 4);
        app_mutex.unlock();
    }

}

void MainWindow::on_btnTurnTray6_clicked(){
    if (app_mutex.tryLock()){
        setTray(ui->btnTurnTray6, 5);
        app_mutex.unlock();
    }
}

// Encender o apagar maquinas
void MainWindow::on_btnWHTurnOn_clicked(){
    if(app_mutex.tryLock()){
        warehouse->isRunning = !warehouse->isRunning;
        setStatusButton(ui->btnWHTurnOn, warehouse->isRunning);
        app_mutex.unlock();
    }
}

void MainWindow::on_btnCM1TurnON_clicked(){
    if(app_mutex.tryLock()){
        chocolateMixer1->isRunning = !chocolateMixer1->isRunning;
        setStatusButton(ui->btnCM1TurnON, chocolateMixer1->isRunning);
        app_mutex.unlock();
    }
}

void MainWindow::on_btnCM2TurnON_clicked(){
    if(app_mutex.tryLock()){
        chocolateMixer2->isRunning = !chocolateMixer2->isRunning;
        setStatusButton(ui->btnCM2TurnON, chocolateMixer2->isRunning);
        app_mutex.unlock();
    }
}

void MainWindow::on_btnDMTurnON_clicked(){
    if(app_mutex.tryLock()){
        doughMixer->isRunning = !doughMixer->isRunning;
        setStatusButton(ui->btnDMTurnON, doughMixer->isRunning);
        app_mutex.unlock();
    }
}

void MainWindow::on_btnAsmTurnON_clicked(){
    if(app_mutex.tryLock()){
        assembler->isRunning = !assembler->isRunning;
        setStatusButton(ui->btnAsmTurnON, assembler->isRunning);
        app_mutex.unlock();
    }
}

void MainWindow::on_btnOvenTurnOn_clicked(){
    if(app_mutex.tryLock()){
        oven->isRunning = !oven->isRunning;
        setStatusButton(ui->btnOvenTurnOn, oven->isRunning);
        app_mutex.unlock();
    }
}

void MainWindow::on_btnPackerTurnOn_clicked(){
    if(app_mutex.tryLock()){
        packer->isRunning = !packer->isRunning;
        app_mutex.unlock();
    }
}

void MainWindow::on_btnTransTurnOn_clicked(){
    if(app_mutex.tryLock()){
        trans->isRunning = !trans->isRunning;
        setStatusButton(ui->btnTransTurnOn, trans->isRunning);
        app_mutex.unlock();
    }
}
