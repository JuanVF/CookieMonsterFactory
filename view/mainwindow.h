#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// UI Stuff
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnPause_clicked();
    void on_btnTurnOn_clicked();

    void on_btnWarehouse_clicked();

    void on_btnPlanner_clicked();

    void on_btnChocMix1_clicked();

    void on_btnChocMix2_clicked();

    void on_btnDoughMix_clicked();

    void on_btnAssembly_clicked();

    void on_btnPlannerApply_clicked();

    void on_btnPlannerAdd_clicked();

    void on_btnPlannerDel_clicked();

    void on_btnAddPack_clicked();

    void on_btnDelPack_clicked();

    void on_btnWHApply_clicked();

    void on_btnAsmApply_clicked();

    void on_btnOven_clicked();

    void on_btnPacker_clicked();

    void on_btnCM2Apply_clicked();

    void on_btnDMApply_clicked();

    void on_btnCM1Apply_clicked();

    void on_btnInspector_clicked();

    void on_btnTrans_clicked();

    void on_btnDeposit_clicked();

    void on_btnOvenApply_clicked();

    void on_btnPackerApply_clicked();

    void on_btnTranApply_clicked();

    void on_btnInspApply_clicked();

    void on_btnTurnTray1_clicked();

    void on_btnTurnTray2_clicked();

    void on_btnTurnTray3_clicked();

    void on_btnTurnTray4_clicked();

    void on_btnTurnTray5_clicked();

    void on_btnTurnTray6_clicked();

    void on_btnWHTurnOn_clicked();

    void on_btnCM1TurnON_clicked();

    void on_btnCM2TurnON_clicked();

    void on_btnDMTurnON_clicked();

    void on_btnAsmTurnON_clicked();

    void on_btnOvenTurnOn_clicked();

    void on_btnPackerTurnOn_clicked();

    void on_btnTransTurnOn_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
