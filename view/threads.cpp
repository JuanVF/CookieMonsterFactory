#include "view/mainwindow.h"
#include <view/mainwindowdata.h>
#include <QPlainTextEdit>
#include <QLabel>
#include <QThread>
#include <QMutex>

class Machines : public QThread {
private:
    QMutex * mutex;
    void setMachines(bool status){
        warehouse->isRunning = status;
        chocolateMixer1->isRunning = status;
        chocolateMixer2->isRunning = status;
        doughMixer->isRunning = status;
        assembler->isRunning = status;
    }

    void resetMachines(){
        planner->reset();
        warehouse->reset();
        chocolateMixer1->reset();
        chocolateMixer2->reset();
        doughMixer->reset();
        assembler->reset();
    }
public:
    void init(QMutex * _mutex){
        mutex = _mutex;
    }

    // Aqui van a ir todos los hilos de las maquinas
    void run(){
        setMachines(true);

        while(isTurnedOn) if (!isInPause && mutex->tryLock()){
            warehouse->checking();
            chocolateMixer1->mix();
            chocolateMixer2->mix();
            doughMixer->mix();
            assembler->assembly();
            mutex->unlock();

            util->delay(1/30);
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

    QPlainTextEdit * lbCM1Pending;
    QPlainTextEdit * lbCM1Processed;

    QPlainTextEdit * lbCM2Pending;
    QPlainTextEdit * lbCM2Processed;

    QPlainTextEdit * lbDMPending;
    QPlainTextEdit * lbDMProcessed;

    QLabel * lbAsmAssembled;
    QLabel * lbAsmChocolate;
    QLabel * lbAsmDough;

    // Se limpian todos los textEdit
    void cleanFields(){
        QMetaObject::invokeMethod(lbCarQueue, "clear");

        QMetaObject::invokeMethod(lbCM1Pending, "clear");
        QMetaObject::invokeMethod(lbCM1Processed, "clear");

        QMetaObject::invokeMethod(lbCM2Pending, "clear");
        QMetaObject::invokeMethod(lbCM2Processed, "clear");

        QMetaObject::invokeMethod(lbDMPending, "clear");
        QMetaObject::invokeMethod(lbDMProcessed, "clear");
    }

    // Settea los datos de los textEdits
    void setFields(){
        string warehouseInfo = warehouse->requestsInfo();

        string cm1Pending = chocolateMixer1->requestsPendingInfo();
        string cm1Processed = chocolateMixer1->requestsProcessedInfo();

        string cm2Pending = chocolateMixer2->requestsPendingInfo();
        string cm2Processed = chocolateMixer2->requestsProcessedInfo();

        string dmPending = doughMixer->requestsPendingInfo();
        string dmProcessed = doughMixer->requestsProcessedInfo();

        string asmProduced = to_string(assembler->assembledCookies);
        string asmChocolate = to_string(assembler->amountChocolate());
        string asmDough = to_string(assembler->amountDough());

        QMetaObject::invokeMethod(lbCarQueue, "setPlainText", Q_ARG(QString, warehouseInfo.c_str()));

        QMetaObject::invokeMethod(lbCM1Pending, "setPlainText", Q_ARG(QString, cm1Pending.c_str()));
        QMetaObject::invokeMethod(lbCM1Processed, "setPlainText", Q_ARG(QString, cm1Processed.c_str()));

        QMetaObject::invokeMethod(lbCM2Pending, "setPlainText", Q_ARG(QString, cm2Pending.c_str()));
        QMetaObject::invokeMethod(lbCM2Processed, "setPlainText", Q_ARG(QString, cm2Processed.c_str()));

        QMetaObject::invokeMethod(lbDMPending, "setPlainText", Q_ARG(QString, dmPending.c_str()));
        QMetaObject::invokeMethod(lbDMProcessed, "setPlainText", Q_ARG(QString, dmProcessed.c_str()));

        QMetaObject::invokeMethod(lbAsmAssembled, "setText", Q_ARG(QString, asmProduced.c_str()));
        QMetaObject::invokeMethod(lbAsmChocolate, "setText", Q_ARG(QString, asmChocolate.c_str()));
        QMetaObject::invokeMethod(lbAsmDough, "setText", Q_ARG(QString, asmDough.c_str()));
    }

public:
    void init(LinkedList<QPlainTextEdit *> * textEdits, LinkedList<QLabel *> * labels, QMutex * _mutex){
        lbCarQueue = textEdits->get(0);

        lbCM1Pending = textEdits->get(1);
        lbCM1Processed = textEdits->get(2);

        lbCM2Pending = textEdits->get(3);
        lbCM2Processed = textEdits->get(4);

        lbDMPending = textEdits->get(5);
        lbDMProcessed = textEdits->get(6);

        lbAsmAssembled = labels->get(0);
        lbAsmChocolate = labels->get(1);
        lbAsmDough = labels->get(2);

        mutex = _mutex;
    }

    void run() {
        while(isTurnedOn) if (!isInPause && mutex->tryLock()){
            cleanFields();
            setFields();

            mutex->unlock();
            util->delay(0.3);
        }
    }
};

