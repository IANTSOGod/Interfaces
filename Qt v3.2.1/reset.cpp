#include "reset.h"
#include "./ui_reset.h"
#include "mainwindow.h"

reset::reset(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::reset)
{
    ui->setupUi(this);
}

reset::~reset()
{
    delete ui;
}

void reset::on_buttonBox_accepted()
{
    system("iptables -F");
    system("iptables -P INPUT ACCEPT");
    system("iptables -P OUTPUT ACCEPT");
    system("iptables -P FORWARD ACCEPT");
    MainWindow* mainwindow=new MainWindow();
    mainwindow->show();
    this->close();
}


void reset::on_buttonBox_rejected()
{
    this->close();
    MainWindow* mainwindow=new MainWindow();
    mainwindow->show();
}

