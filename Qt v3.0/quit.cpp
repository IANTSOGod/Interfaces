#include "quit.h"
#include "./ui_quit.h"
#include "mainwindow.h"

Quit::Quit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Quit)
{
    ui->setupUi(this);
}

Quit::~Quit()
{
    delete ui;
}
void Quit::on_buttonBox_accepted()
{
    this->close();
    emit closeMainWindow();
}


void Quit::on_buttonBox_rejected()
{
    MainWindow* mainwindow=new MainWindow();
    mainwindow->show();
    this->close();
}

