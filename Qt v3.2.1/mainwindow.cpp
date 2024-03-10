#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "reset.h"
#include "quit.h"
#include "./ui_quit.h"
#include "./ui_reset.h"
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
void MainWindow::getList(){

    std::ifstream fichier("list.txt"); // Ouvrir le fichier en lecture

    std::string ligne;
    bool dansChainInput = false;
    bool dansChainForward = false;
    bool dansChainOutput = false;
    int lignesEntreChainInputForward = 0;
    int lignesEntreChainForwardOutput = 0;
    int lignesEntreChainOutputFin = 0;

    while (std::getline(fichier, ligne)) {
        if (ligne.find("Chain INPUT") != std::string::npos) {
            dansChainInput = true;
            continue;
        }

        if (dansChainInput && ligne.find("Chain FORWARD") != std::string::npos) {
            dansChainInput = false;
            dansChainForward = true;
            continue;
        }

        if (dansChainForward && ligne.find("Chain OUTPUT") != std::string::npos) {
            dansChainForward = false;
            dansChainOutput = true;
            continue;
        }

        if (dansChainInput && !dansChainForward) {
            ++lignesEntreChainInputForward;
        }

        if (dansChainForward && !dansChainOutput) {
            ++lignesEntreChainForwardOutput;
        }

        if (dansChainOutput) {
            ++lignesEntreChainOutputFin;
        }
    }
    longueurINPUT=lignesEntreChainInputForward-2;
    longueurFORWARD=lignesEntreChainInputForward-1;
    longueurOUTPUT=lignesEntreChainOutputFin-1;
    fichier.close();
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
    quit=new Quit(this);
    connect(quit, &Quit::closeMainWindow,this,&MainWindow::close);
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
    ui->pushButton_2->setText("delete rules");
    // Mettre à jour les longueurs en fonction du fichier
    getList();

    // Crée un nouveau widget pour contenir les radioboutons
    QWidget* widget = new QWidget;

    // Crée un layout vertical pour le widget
    QVBoxLayout* layout = new QVBoxLayout(widget);

    // Parcourt la liste des commandes
    for (int i = 0; i < list_cmd.size(); i++) {
        // Crée un nouveau QRadioButton avec le texte de la i-ème commande
        QRadioButton* radio = new QRadioButton(list_cmd[i]);

        // Ajoute le QRadioButton au layout vertical
        layout->addWidget(radio);
        int lineNum = -1;
        for (int j = 0; j < list_cmd.size(); j++) {
            if (list_cmd[j] == radio->text()) {
                lineNum = j + 1; // On ajoute 1 pour correspondre à la numérotation réelle des lignes
                break;
            }
        }

    if (lineNum != -1) {
        // Connecte le signal clicked du QRadioButton à une lambda
        connect(radio, &QRadioButton::clicked, [lineNum,this, i,layout,radio](bool checked) {
            QString deletable;

            if (checked) {
                // Vérifie le type de cible (INPUT ou OUTPUT) et construit la commande correspondante
                if (list_target[i] == "INPUT") {
                    if (i < longueurINPUT) {
                        deletable = "iptables -D INPUT " + QString::number(lineNum);
                        --longueurINPUT;
                    }
                } else {
                    if (list_target[i] == "OUTPUT") {
                        if (i < longueurOUTPUT) {
                            deletable = "iptables -D OUTPUT " + QString::number(lineNum);
                            --longueurOUTPUT;
                        }
                    } else if(list_target[i] == "FORWARD"){
                        if (i < longueurFORWARD) {
                            deletable = "iptables -D FORWARD " + QString::number(lineNum);
                            --longueurFORWARD;
                        }
                    }
                }
                // Appelle la fonction prompt avec la commande à supprimer
                prompt(deletable);

                // Supprime l'élément de la liste des commandes
                list_cmd.erase(list_cmd.begin() + i);
                list_target.erase(list_target.begin() + i);
                // On enlève le radiobouton du layout
                layout->removeWidget(radio);
                // On le supprime de la mémoire
                radio->deleteLater();
                ui->stackedWidget->setCurrentIndex(0);
                ui->pushButton_2->setText("click to confirm the deletion ?");
            }
        });
    }
    }

    // Définir le nouveau widget comme widget du scrollArea2
    ui->scrollArea_2->setWidget(widget);

    // Changer l'index du stackedWidget après avoir créé et connecté les radioboutons
    ui->stackedWidget->setCurrentIndex(1);
    QString tmp=getTables();
    ui->textEdit->setText(tmp);
}




void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    QString tmp=getTables();
    ui->textEdit->setText(tmp);
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
    list_target.push_back(typeTarget);
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

static void identify(QString tmp,QString portEq,QString typeTarget,QString portValue){
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
    this->close();
    res->show();
}


void MainWindow::on_pushButton_26_clicked()
{
    this->close();
    quit->show();
}


void MainWindow::on_pushButton_27_clicked()
{
    system("iptables -F");
    system("iptables -P INPUT DROP");
    system("iptables -P OUTPUT DROP");
    system("iptables -P FORWARD DROP");
    QString tmp=getTables();
    ui->textEdit->setText(tmp);
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_28_clicked()
{
    system("iptables -F");
    system("iptables -P INPUT ACCEPT");
    system("iptables -P OUTPUT ACCEPT");
    system("iptables -P FORWARD ACCEPT");
    QString tmp=getTables();
    ui->textEdit->setText(tmp);
    ui->stackedWidget->setCurrentIndex(0);
}

