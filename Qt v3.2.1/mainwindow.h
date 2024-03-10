#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QRadioButton>
#include "reset.h"
#include "quit.h"
#include "./ui_quit.h"
#include "./ui_reset.h"
#include "./ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int longueurINPUT;
    int longueurOUTPUT;
    int longueurFORWARD;
    Quit* quit;
    reset* res=new reset(this);
    std::vector<QString> list_target;
    std::vector<QRadioButton> list_button;
    std::vector<QString> list_cmd;
    QString typeTarget;
    QString choicePolicy;
    QString typePort;
    QString portValue;
    QString typeDNS;
    QString adress;
    QString typeMac;
    QString macAdress;
    QString cmd;
    QString text="iptables -A";
    MainWindow(QWidget *parent = nullptr);
    void getList();
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_13_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_28_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
