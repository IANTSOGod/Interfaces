#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <QByteArray>
#include <QRadioButton>
#include <QtWidgets>

void prompt(QString cmd){
    QByteArray array=cmd.toUtf8();
    char c[array.size()+1];
    array.data()[array.size()]='\0';
    std::copy(array.constData(),array.constData()+array.size() + 1,c);
    FILE* file=fopen("test.txt","w");
    fprintf(file,"%s",c);
    fclose(file);
    system(c);
}
QString getTables(){
    QString t;
    system("iptables -L > list.txt");
    std::ifstream fichier("list.txt");
    if(fichier.is_open()){
        std::string ligne;
        while(std::getline(fichier,ligne)){
            t+=(QString::fromStdString(ligne))+"\n";
        }
    }
    return t;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString tmp=getTables();
    ui->textEdit->setText(tmp);
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_2_clicked()
{
    // Crée un nouveau widget
    QWidget* widget = new QWidget;

    // Crée un layout vertical pour le widget
    QVBoxLayout* layout = new QVBoxLayout(widget);

    // Définit le widget comme contenu de la scrollArea_2
    ui->scrollArea_2->setWidget(widget);

    // Change l'index de la page actuelle du stackedWidget à 1
    ui->stackedWidget->setCurrentIndex(1);

    // Parcourt la liste des commandes
    for (int i = 0; i < list_cmd.size(); i++) {
        // Crée un nouveau QRadioButton avec le texte de la i-ème commande
        QRadioButton* radio = new QRadioButton(list_cmd[i]);

        // Connecte le signal toggled du QRadioButton à une fonction lambda
        connect(radio, &QRadioButton::toggled, [this, i, radio]() {
            QString deletable;
            if (radio->isChecked()) {
                // Vérifie le type de cible (INPUT ou OUTPUT) et construit la commande correspondante
                if (typeTarget == "INPUT") {
                    deletable = "iptables -D INPUT " + QString::number(i + 1);
                } else {
                    deletable = "iptables -D OUTPUT " + QString::number(i + 1);
                }
                // Appelle la fonction prompt avec la commande à supprimer
                prompt(deletable);
            }
        });

        // Ajoute le QRadioButton au layout vertical
        layout->addWidget(radio);
    }
}



void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_6_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(2);
    typePort=" -p ";
    ui->lineEdit_2->setText(text+" "+typeTarget+" -j "+choicePolicy+typePort);
}


void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
    typeTarget=(ui->pushButton_8)->text();
    ui->lineEdit_2->setText(text+" "+typeTarget);
}


void MainWindow::on_pushButton_9_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
    typeTarget=(ui->pushButton_9)->text();
    ui->lineEdit_2->setText(text+" "+typeTarget);
}


void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(1);
    typeTarget=(ui->pushButton_10)->text();
    ui->lineEdit_2->setText(text+" "+typeTarget);
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(2);
    if(typeTarget=="INPUT"){
        typeDNS=" -s ";
    }
    else{
        typeDNS=" -d ";
    }
}


void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(1);
}


void MainWindow::on_pushButton_16_clicked()
{
    ui->stackedWidget_3->setCurrentIndex(0);
}


void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}


void MainWindow::on_pushButton_14_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0);
}


void MainWindow::on_pushButton_7_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(1);
    ui->lineEdit_2->setText(text+" "+typeTarget+" -j "+choicePolicy);
}


void MainWindow::on_pushButton_13_clicked()
{
    ui->lineEdit_2->setText(cmd);
    list_cmd.push_back(cmd);
    prompt(cmd);
    QString tmp=getTables();
    ui->textEdit->setText(tmp);
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget_3->setCurrentIndex(0);
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->stackedWidget_4->setCurrentIndex(0);
    ui->stackedWidget_5->setCurrentIndex(0);
}


void MainWindow::on_radioButton_clicked()
{
    choicePolicy=ui->radioButton->text();
    ui->lineEdit_2->setText(text+" "+typeTarget+" -j "+choicePolicy);
}


void MainWindow::on_radioButton_2_clicked()
{
    choicePolicy=ui->radioButton_2->text();
    ui->lineEdit_2->setText(text+" "+typeTarget+" -j "+choicePolicy);
}


void MainWindow::on_radioButton_3_clicked()
{
    choicePolicy=ui->radioButton_3->text();
    ui->lineEdit_2->setText(text+" "+typeTarget+" -j "+choicePolicy);
}


void MainWindow::on_pushButton_17_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}

void identify(QString tmp,QString portEq,QString typeTarget,QString portValue){
    if(typeTarget=="INPUT"){
        tmp=" -p "+portEq+" --sport "+portValue;
    }
    else{
        tmp=" -p "+portEq+" --dport "+portValue;
    }
}

void MainWindow::on_pushButton_18_clicked()
{
    QString portEq;
    QString tmp;
    ui->stackedWidget_2->setCurrentIndex(1);
    portValue=ui->lineEdit_7->text();
    switch(portValue.toInt()){
        case 21:
            portEq="ftp";
            break;
        case 23:
            portEq="telnet";
            break;
        case 22:
            portEq="ssh";
            break;
        case 443:
            portEq="tcp";
            break;
        case 53:
            portEq="udp";
            break;
        case 80:
            portEq="tcp";
            break;
        default:
            portEq="";
            break;
    }
    if(portEq!=""){
        if(typeTarget=="INPUT"){
            tmp=" -p "+portEq+" --sport "+portValue;
        }
        else{
            tmp=" -p "+portEq+" --dport "+portValue;
        }
    }
    portValue=tmp;
    ui->lineEdit_2->setText(text+" "+typeTarget+" -j "+choicePolicy+portValue);
}


void MainWindow::on_pushButton_19_clicked()
{
    ui->stackedWidget_4->setCurrentIndex(0);
}


void MainWindow::on_pushButton_20_clicked()
{
    adress=ui->lineEdit_5->text();
    ui->lineEdit_2->setText(text+" "+typeTarget+" -j "+choicePolicy+portValue+typeDNS+adress);
    ui->stackedWidget_4->setCurrentIndex(1);
}


void MainWindow::on_pushButton_21_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(1);
    typeMac=" -m ";
}


void MainWindow::on_pushButton_22_clicked()
{
    cmd=text+" "+typeTarget+" -j "+choicePolicy+portValue+typeDNS+adress;
    ui->stackedWidget_5->setCurrentIndex(2);
}

void MainWindow::on_pushButton_24_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(0);
}

void MainWindow::on_pushButton_25_clicked()
{
    ui->stackedWidget_5->setCurrentIndex(0);
}


void MainWindow::on_pushButton_23_clicked()
{
    QString mac;
    QString tmp;
    macAdress=(ui->lineEdit_6)->text();
    cmd=text+" "+typeTarget+" -j "+choicePolicy+portValue+typeDNS+adress+typeMac+macAdress+" --mac-source ";
    ui->lineEdit_2->setText(text+" "+typeTarget+" -j "+choicePolicy+portValue+typeDNS+adress+typeMac+macAdress+" --mac-source ");
}

void MainWindow::on_pushButton_3_clicked()
{
    system("iptables -P INPUT ACCEPT");
    system("iptables -P OUTPUT ACCEPT");
    system("iptables -P FORWARD ACCEPT");
    system("iptables -F");
    ui->stackedWidget->setCurrentIndex(0);
    QString tmp=getTables();
    ui->textEdit->setText(tmp);
}

