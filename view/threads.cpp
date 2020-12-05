#include "view/mainwindow.h"
#include <view/mainwindowdata.h>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QThread>
#include <QMutex>

void setStatusButton(QPushButton * btn, bool status){
    if (status){
        btn->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(0, 170, 0);border-radius: 10px;");
    } else {
        btn->setStyleSheet("color: rgb(255, 255, 255);background-color: rgb(194, 69, 31);border-radius: 10px;");
    }
}

class Machines : public QThread {
private:
    QMutex * mutex;
    void setMachines(bool status){
        warehouse->isRunning = status;
        chocolateMixer1->isRunning = status;
        chocolateMixer2->isRunning = status;
        doughMixer->isRunning = status;
        assembler->isRunning = status;
        oven->isRunning = status;
        trans->isRunning = status;
        packer->isRunning = status;
    }

    void resetMachines(){
        planner->reset();
        warehouse->reset();
        chocolateMixer1->reset();
        chocolateMixer2->reset();
        doughMixer->reset();
        assembler->reset();
        trans->reset();
        oven->restartOven();
    }

    void initTimes(){
        warehouse->car->started = clock();
        chocolateMixer1->started = clock();
        chocolateMixer2->started = clock();
        doughMixer->started = clock();
        assembler->started = clock();
        trans->initClocks();
    }

public:
    void init(QMutex * _mutex){
        mutex = _mutex;
    }

    bool canMachinesStart(){
        QMessageBox msgBox;
        bool can = true;

        if (!planner->canStart()){
            msgBox.setText("No se puede iniciar. Verifique el planificador...");
            can = false;
        } else if (!warehouse->canStart()){
            msgBox.setText("No se puede iniciar. Verifique el almacen...");
            can = false;
        } else if (!chocolateMixer1->canStart()){
            msgBox.setText("No se puede iniciar. Verifique la mezcladora de chocolate 1...");
            can = false;
        } else if (!chocolateMixer2->canStart()){
            msgBox.setText("No se puede iniciar. Verifique la mezcladora de chocolate 2...");
            can = false;
        } else if (!doughMixer->canStart()){
            msgBox.setText("No se puede iniciar. Verifique la mezcladora de masa...");
            can = false;
        } else if (!oven->canStart()){
            msgBox.setText("No se puede iniciar. Verifique el horno o los inspectores...");
            can = false;
        } else if (!packer->canStart()){
            msgBox.setText("No se puede iniciar. Verifique la empacadora...");
            can = false;
        } else if (!trans->canStart()){
            msgBox.setText("No se puede iniciar. Verifique los transportes...");
            can = false;
        }

        if (!can)
            msgBox.exec();

        return can;
    }

    // Aqui van a ir todos los hilos de las maquinas
    void run(){
        setMachines(true);

        initTimes();
        packer->prepare();
        trans->init();
        trans->initClocks();
        deposit->init();

        while(isTurnedOn) if (!isInPause & mutex->tryLock()){
            warehouse->checking();
            chocolateMixer1->mix();
            chocolateMixer2->mix();
            doughMixer->mix();
            assembler->assembly();
            oven->start();
            packer->working();
            trans->send();

            mutex->unlock();

            util->delay(1/10);
        }

        setMachines(false);
        resetMachines();
    }
};

// Esta clase es para los hilos de la UI
class UIThread : public QThread {
private:
    QMutex * mutex;
    QPlainTextEdit * lbCarQueue;

    QPlainTextEdit * teCM1Pending;
    QPlainTextEdit * teCM1Processed;
    QLabel * lbCM1Processed;

    QPlainTextEdit * teCM2Pending;
    QPlainTextEdit * teCM2Processed;
    QLabel * lbCM2Processed;

    QPlainTextEdit * teDMPending;
    QPlainTextEdit * teDMProcessed;
    QLabel * lbDMProcessed;

    QLabel * lbAsmAssembled;
    QPlainTextEdit * lbAsmChocolate;
    QPlainTextEdit * lbAsmDough;

    QPlainTextEdit * teOvenTrayInfo;
    QLabel * lbOvenCooking;
    QLabel * lbOvenMaxCookies;
    QLabel * lbOvenWaiting;

    QLabel * lbInspDel1;
    QLabel * lbInspDel2;

    QPlainTextEdit * lbDepositPacks;
    QLabel * lbDepositTotal;

    QPlainTextEdit * tePackerPacked;
    QPlainTextEdit * teTrans;

    QPushButton * btnStateWH;

    QPushButton * btnStateCM1;
    QPushButton * btnStateCM2;
    QPushButton * btnStateDM;

    QPushButton * btnStateAsm;
    QPushButton * btnStateOven;
    QPushButton * btnStateInsp;

    // Setea el estado de los botones
    void checkButtonsState(){
        setStatusButton(btnStateWH, warehouse->isRunning);

        setStatusButton(btnStateCM1, chocolateMixer1->isRunning);
        setStatusButton(btnStateCM2, chocolateMixer2->isRunning);
        setStatusButton(btnStateDM, doughMixer->isRunning);

        setStatusButton(btnStateAsm, assembler->isRunning);
        setStatusButton(btnStateOven, oven->isRunning);
        setStatusButton(btnStateInsp, trans->isRunning);
    }

    // Se limpian todos los textEdit
    void cleanFields(){
        QMetaObject::invokeMethod(lbCarQueue, "clear");

        QMetaObject::invokeMethod(teCM1Pending, "clear");
        QMetaObject::invokeMethod(teCM1Processed, "clear");

        QMetaObject::invokeMethod(teCM2Pending, "clear");
        QMetaObject::invokeMethod(teCM2Processed, "clear");

        QMetaObject::invokeMethod(teDMPending, "clear");
        QMetaObject::invokeMethod(teDMProcessed, "clear");

        QMetaObject::invokeMethod(teOvenTrayInfo, "clear");
    }

    // Settea los datos de los textEdits
    void setFields(){
        string warehouseInfo = warehouse->requestsInfo();

        string cm1Pending = chocolateMixer1->requestsPendingInfo();
        string cm1Processed = chocolateMixer1->requestsProcessedInfo();
        string cm1Total = "Chocolate procesado: " + to_string(chocolateMixer1->total) + "gr";

        string cm2Pending = chocolateMixer2->requestsPendingInfo();
        string cm2Processed = chocolateMixer2->requestsProcessedInfo();
        string cm2Total = "Chocolate procesado: " + to_string(chocolateMixer2->total) + "gr";

        string dmPending = doughMixer->requestsPendingInfo();
        string dmProcessed = doughMixer->requestsProcessedInfo();
        string dmTotal = "Masa procesada: " + to_string(doughMixer->total) + "gr";

        string asmProduced = "Galletas ensambladas: " + to_string(assembler->assembledCookies);
        string asmChocolate = assembler->chocolateInfo();
        string asmDough = assembler->doughInfo();

        string ovenTrayInfo = oven->getTraysInfo();
        string ovenWaiting = "En espera: " + to_string(oven->galletasEnEspera());
        string max = "Max Galletas: " + to_string(oven->capacity);
        string cooked = "Horneadas: " + to_string(oven->galletasHorneadas());

        string rechazadas1 = to_string(oven->inspectores->get(0)->rechazadas);
        string rechazadas2 = to_string(oven->inspectores->get(1)->rechazadas);

        string packerInfo = packer->getInfo();
        string transInfo = trans->getInfo();

        string depositInfo = deposit->getInfo();
        string depositTotal = to_string(deposit->totalInDeposit());

        QMetaObject::invokeMethod(lbCarQueue, "setPlainText", Q_ARG(QString, warehouseInfo.c_str()));

        QMetaObject::invokeMethod(teCM1Pending, "setPlainText", Q_ARG(QString, cm1Pending.c_str()));
        QMetaObject::invokeMethod(teCM1Processed, "setPlainText", Q_ARG(QString, cm1Processed.c_str()));
        QMetaObject::invokeMethod(lbCM1Processed, "setText", Q_ARG(QString, cm1Total.c_str()));

        QMetaObject::invokeMethod(teCM2Pending, "setPlainText", Q_ARG(QString, cm2Pending.c_str()));
        QMetaObject::invokeMethod(teCM2Processed, "setPlainText", Q_ARG(QString, cm2Processed.c_str()));
        QMetaObject::invokeMethod(lbCM2Processed, "setText", Q_ARG(QString, cm2Total.c_str()));

        QMetaObject::invokeMethod(teDMPending, "setPlainText", Q_ARG(QString, dmPending.c_str()));
        QMetaObject::invokeMethod(teDMProcessed, "setPlainText", Q_ARG(QString, dmProcessed.c_str()));
        QMetaObject::invokeMethod(lbDMProcessed, "setText", Q_ARG(QString, dmTotal.c_str()));

        QMetaObject::invokeMethod(lbAsmAssembled, "setText", Q_ARG(QString, asmProduced.c_str()));
        QMetaObject::invokeMethod(lbAsmChocolate, "setPlainText", Q_ARG(QString, asmChocolate.c_str()));
        QMetaObject::invokeMethod(lbAsmDough, "setPlainText", Q_ARG(QString, asmDough.c_str()));

        QMetaObject::invokeMethod(teOvenTrayInfo, "setPlainText", Q_ARG(QString, ovenTrayInfo.c_str()));
        QMetaObject::invokeMethod(lbOvenCooking, "setText", Q_ARG(QString, cooked.c_str()));
        QMetaObject::invokeMethod(lbOvenMaxCookies, "setText", Q_ARG(QString, max.c_str()));
        QMetaObject::invokeMethod(lbOvenWaiting, "setText", Q_ARG(QString, ovenWaiting.c_str()));

        QMetaObject::invokeMethod(teTrans, "setPlainText", Q_ARG(QString, transInfo.c_str()));
        QMetaObject::invokeMethod(lbInspDel1, "setText", Q_ARG(QString, rechazadas1.c_str()));
        QMetaObject::invokeMethod(lbInspDel2, "setText", Q_ARG(QString, rechazadas2.c_str()));

        QMetaObject::invokeMethod(lbDepositPacks, "setPlainText", Q_ARG(QString, depositInfo.c_str()));
        QMetaObject::invokeMethod(lbDepositTotal, "setText", Q_ARG(QString, depositTotal.c_str()));
    }

public:
    void init(LinkedList<QPlainTextEdit *> * textEdits, LinkedList<QLabel *> * labels, LinkedList<QPushButton *> * buttons, QMutex * _mutex){
        lbCarQueue = textEdits->get(0);

        teCM1Pending = textEdits->get(1);
        teCM1Processed = textEdits->get(2);

        teCM2Pending = textEdits->get(3);
        teCM2Processed = textEdits->get(4);

        teDMPending = textEdits->get(5);
        teDMProcessed = textEdits->get(6);

        lbAsmAssembled = labels->get(0);
        lbAsmChocolate = textEdits->get(7);
        lbAsmDough = textEdits->get(8);

        lbCM1Processed = labels->get(1);
        lbCM2Processed = labels->get(2);
        lbDMProcessed = labels->get(3);

        teOvenTrayInfo = textEdits->get(9);
        lbOvenCooking = labels->get(4);
        lbOvenMaxCookies = labels->get(5);
        lbOvenWaiting = labels->get(6);

        tePackerPacked = textEdits->get(10);
        teTrans = textEdits->get(11);

        lbInspDel1 = labels->get(7);
        lbInspDel2 = labels->get(8);
        lbDepositPacks = textEdits->get(12);
        lbDepositTotal = labels->get(9);

        btnStateWH = buttons->get(0);

        btnStateCM1 = buttons->get(1);
        btnStateCM2 = buttons->get(2);
        btnStateDM = buttons->get(3);

        btnStateAsm = buttons->get(4);
        btnStateOven = buttons->get(5);
        btnStateInsp = buttons->get(6);

        mutex = _mutex;
    }

    void run() {
        while(isTurnedOn) if (!isInPause & mutex->tryLock()){
            cleanFields();
            setFields();
            checkButtonsState();

            mutex->unlock();
            util->delay(1);
        }

        cleanFields();
    }
};

