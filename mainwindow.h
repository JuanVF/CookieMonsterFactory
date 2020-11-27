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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
