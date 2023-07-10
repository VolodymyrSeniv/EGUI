#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h>
#include "dialog.h"
#include <QObject>
using namespace std;



QString MainWindow::getId(){
return selectedID;
}

void MainWindow::setId(QString someID){
selectedID = someID;
}

QString MainWindow::getEmail(){
return selectedEmail;
}

void MainWindow::setEmail(QString someEmail){
selectedEmail = someEmail;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->createYourID->setPlaceholderText("Create your ID");
    ui->createYourPassword->setPlaceholderText("Create your Password");
    ui->emailAddress->setPlaceholderText("Enter your email");
    ui->yourPassword->setPlaceholderText("Provide your password");
    ui->yourID->setPlaceholderText("Provide your ID");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()//registration
{

    QString createdID = ui->createYourID->text();
    QString createdPassword = ui->createYourPassword->text();
    QString createdEmail = ui->emailAddress->text();
    if(createdID.isEmpty() || createdPassword.isEmpty() || createdEmail.isEmpty()){
        QMessageBox::warning(nullptr,"Information","Please provide full information about your account");
       return;
    }
    QFile file("fjs.json");
    if(file.open(QIODevice::ReadOnly|QFile::Text)){
        doc = QJsonDocument::fromJson(QByteArray(file.readAll()),&docError);
        file.close();
        if(docError.errorString().toInt()==QJsonParseError::NoError){
            //array of objects
            docAr = QJsonValue(doc.object().value("blogger")).toArray();
        }
        for(int i=0; i<docAr.count();i++){
        if(createdID==docAr.at(i).toObject().value("ID").toString() ){
            QMessageBox::warning(nullptr,"Information","Such ID already exists");
            ui->createYourID->clear();
            ui->createYourPassword->clear();
            ui->emailAddress->clear();
           return;
        }
        }
}
    if (file.open(QIODevice::WriteOnly) )
    {

        QVariantMap map;
        map.insert("ID", ui->createYourID->text());
        map.insert("Password", ui->createYourPassword->text());
        map.insert("Email", ui->emailAddress->text());

        QJsonObject adding = QJsonObject::fromVariantMap(map);

        QJsonArray docToWrite = doc.object().value("blogger").toArray();
        docToWrite.append(adding);
        doc.setArray(docToWrite);

        file.write("{\"blogger\":"+doc.toJson()+"}");
        file.close();

        ui->createYourID->clear();
        ui->createYourPassword->clear();
        ui->emailAddress->clear();
        QMessageBox::information(nullptr,"Information","You were successfuly registered");
    }
    else{
        QMessageBox::warning(nullptr,"Error","Can not open the file");
        ui->createYourID->clear();
        ui->createYourPassword->clear();
        ui->emailAddress->clear();
    }
}



void MainWindow::on_pushButton_clicked()//login
{
    int temp = 0;

    QString userId = ui->yourID->text();
    QString password = ui->yourPassword->text();
    QString userEmail;

if(userId.isEmpty() || password.isEmpty()){
 QMessageBox::warning(this,"Login","You have to provide you account information");
 return;
}

    QFile file("fjs.json");
    if(file.open(QIODevice::ReadOnly|QFile::Text)){
        doc = QJsonDocument::fromJson(QByteArray(file.readAll()),&docError);
        file.close();

        if(docError.errorString().toInt()==QJsonParseError::NoError){
            //array of objects
            docAr = QJsonValue(doc.object().value("blogger")).toArray();
            for(int i = 0; i<docAr.count();i++){

               if(userId==docAr.at(i).toObject().value("ID").toString() && password==docAr.at(i).toObject().value("Password").toString()) {
                   temp = 1;

                  userEmail = docAr.at(i).toObject().value("Email").toString();
                  QMessageBox::information(this,"Login","Username and password are correct");
                  hide();
                  userWindow = new UserWindow(this);

                  userWindow->windowModality();
                  userWindow->showMaximized();

               }

            }
            if(temp==0){
                QMessageBox::warning(this,"Login","Username and password are incorrect or there is no such a user");
                ui->yourID->clear();
                ui->yourPassword->clear();
            }
        }
     }

        else {
        QMessageBox::warning(nullptr,"info", "File cannot be openned");

    }

   QObject::connect(this,SIGNAL(SendID(QString)),userWindow,SLOT(GetID(QString)));
   emit(SendID(userId));
   QObject::connect(this,SIGNAL(SendEmail(QString)),userWindow,SLOT(GetEmail(QString)));
   emit(SendEmail(userEmail));
}

