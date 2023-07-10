#include "userwindow.h"
#include "ui_userwindow.h"
#include "mainwindow.h"


UserWindow::UserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserWindow)
{
    ui->setupUi(this); 
    ui->userEmailLabel->setText("User ID");
    ui->userIDLabel->setText("User Email");
    ui->label_3->setText("Time and Date of publication: ");

}


UserWindow::~UserWindow()
{
    delete ui;
}


void UserWindow::on_pushButton_clicked() //Open
{
    int temp = 0;
    QString blogID = ui->textEdit->toPlainText();
if(blogID.isEmpty()){
QMessageBox::warning(this,"Information","Can not open the blog whithout its id" + file.errorString());
}

    /*globPath = QFileDialog::getOpenFileName(nullptr,"","","*.json");
    file.setFileName(globPath); this command causes problems with the window, actually after procceding it closes*/
    //if( textEdit->isEmpty()){}

     QFile file("jsn.json");
    if(file.open(QIODevice::ReadOnly|QFile::Text)){
        doc = QJsonDocument::fromJson(QByteArray(file.readAll()), &docError);
        file.close();
        if(docError.errorString().toInt()==QJsonParseError::NoError){
            docAr = QJsonValue(doc.object().value("blogg")).toArray();
            for(int i = 0; i<docAr.count(); i++){
                if(blogID == docAr[i].toObject().value("ID").toString()){
                temp = 1;
                    ui->textEdit->setText(docAr[i].toObject().value("ID").toString());
                    ui->textEdit_3->setText(docAr[i].toObject().value("Title").toString());
                    ui->textEdit_2->setText(docAr[i].toObject().value("Main").toString());
                    ui->label_3->setText("Time and Date of publication: " + docAr[i].toObject().value("Time").toString());
                }

            }
            if(temp==0){

                QMessageBox::warning(this,"Information","There is no such a blog whith this id " + file.errorString());
                ui->textEdit->clear();
                ui->textEdit_3->clear();
                ui->textEdit_2->clear();
                ui->label_3->clear();
                return;
            }

    }
   else{
        QMessageBox::warning(this,"Information","Can not open the file " + file.errorString());
        ui->textEdit->clear();
        ui->textEdit_3->clear();
        ui->textEdit_2->clear();
        }

    }

}


void UserWindow::on_pushButton_3_clicked() // creating a new blogg
{
    QString blogID = ui->textEdit->toPlainText();
    QString blogMain = ui->textEdit_2->toPlainText();
    QString blogTitle = ui->textEdit_3->toPlainText();
    if(blogID.isEmpty()||blogMain.isEmpty()||blogTitle.isEmpty()){
        QMessageBox::warning(this,"Information","You cannot create a blog without an ID and with any blog written");
        return;
    }
    QFile file("jsn.json");
    QDateTime time = QDateTime::currentDateTime();
    QString time_string = time.toString();
    if(file.open(QIODevice::ReadOnly|QFile::Text)){
        doc = QJsonDocument::fromJson(QByteArray(file.readAll()), &docError);
        file.close();
        if(docError.errorString().toInt()==QJsonParseError::NoError){
            docAr = QJsonValue(doc.object().value("blogg")).toArray();
            for(int i = 0; i<docAr.count(); i++){
               if(blogID == docAr[i].toObject().value("ID").toString()){
                QMessageBox::warning(this,"Information","You cannot create a blog with already used ID");
                ui->textEdit->clear();
                ui->textEdit_3->clear();
                ui->textEdit_2->clear();
                return;
                }
            }
    }
}
    if(file.open(QIODevice::WriteOnly)){
        QVariantMap map;
        map.insert("ID", ui->textEdit->toPlainText());
        map.insert("Title", ui->textEdit_3->toPlainText());
        map.insert("Main", ui->textEdit_2->toPlainText());
        map.insert("Time", time_string);

        QJsonObject adding = QJsonObject::fromVariantMap(map);

        QJsonArray docToWrite = doc.object().value("blogg").toArray();
        docToWrite.append(adding);
        doc.setArray(docToWrite);

        file.write("{\"blogg\":"+doc.toJson()+"}");
        file.close();
        ui->textEdit->clear();
        ui->textEdit_3->clear();
        ui->textEdit_2->clear();
        ui->label_3->clear();
        QMessageBox::information(this,"Information","You successfully created your new blog");

    }
    else{
         QMessageBox::warning(this,"Information","Can not open the file " + file.errorString());
         ui->textEdit->clear();
         ui->textEdit_3->clear();
         ui->textEdit_2->clear();

         }
}



void UserWindow::on_pushButton_2_clicked() //rewrite the existing blog
{
QString blogID = ui->textEdit->toPlainText();
QString blogMain = ui->textEdit_2->toPlainText();
QString blogTitle = ui->textEdit_3->toPlainText();
QDateTime time = QDateTime::currentDateTime();
QString time_string = time.toString();
QFile file("jsn.json");
bool temp = true;
if(blogID.isEmpty()||blogMain.isEmpty()||blogTitle.isEmpty()){
    QMessageBox::warning(this,"Information","You cannot modify a blog without an ID or without blog written");
    return;
}
if(file.open(QIODevice::ReadOnly|QFile::Text)){
    doc = QJsonDocument::fromJson(QByteArray(file.readAll()), &docError);
    file.close();
}
    if(docError.errorString().toInt()==QJsonParseError::NoError){
        docAr = QJsonValue(doc.object().value("blogg")).toArray();
        for(int i = 0; i < docAr.count(); i ++){
           if(blogID == docAr[i].toObject().value("ID").toString()){
               if(file.open(QIODevice::WriteOnly)){

               QVariantMap map;
               map.insert("ID", blogID);
               map.insert("Title", blogTitle);
               map.insert("Main", blogMain);
               map.insert("Time", time_string);
               QJsonObject adding = QJsonObject::fromVariantMap(map);
               docAr.replace(i,adding);
               doc.setArray(docAr);
temp = false;
               QMessageBox::information(this,"Information","You successfully modify your blog");
               }
           }



           file.write("{\"blogg\":"+doc.toJson()+"}");
           file.close();
           ui->textEdit->clear();
           ui->textEdit_3->clear();
           ui->textEdit_2->clear();

           }
        if(temp == true){


        QMessageBox::warning(this,"Information","There is no such a blog to modify");
        ui->textEdit->clear();
        ui->textEdit_3->clear();
        ui->textEdit_2->clear();
        ui->label_3->clear();
        }

    }

  }




void UserWindow::on_actionClear_Title_triggered()//clear title
{
    ui->textEdit_3->clear();
}


void UserWindow::on_actionClear_Blog_content_triggered()//clear blog title
{
    ui->textEdit_2->clear();
}


void UserWindow::on_actionClear_blog_ID_triggered()//clear blog ID
{
     ui->textEdit->clear();
}


void UserWindow::on_actionClear_all_triggered()//clear all
{
       ui->textEdit->clear();
        ui->textEdit_2->clear();
        ui->textEdit_3->clear();
        ui->label_3->clear();


}


void UserWindow::on_actionShow_all_blogs_triggered()//open a new window to show a table of blogs
{
    dialog = new Dialog(this);
    dialog->setModal(true);
    dialog->show();
}




void UserWindow::on_actionDelete_2_triggered()
{
    QString blogID = ui->textEdit->toPlainText();
    QString blogMain = ui->textEdit_2->toPlainText();
    QString blogTitle = ui->textEdit_3->toPlainText();
    QDateTime time = QDateTime::currentDateTime();
    QString time_string = time.toString();
    int i;
    bool temp = true;
    QFile file("jsn.json");
    if(blogID.isEmpty()){
        QMessageBox::warning(this,"Information","You cannot delete a blog without an ID");
        return;
    }
    if(file.open(QIODevice::ReadOnly|QFile::Text)){
        doc = QJsonDocument::fromJson(QByteArray(file.readAll()), &docError);
        file.close();
    if(docError.errorString().toInt()==QJsonParseError::NoError){
        docAr = QJsonValue(doc.object().value("blogg")).toArray();
        for(i = 0; i<docAr.count(); i++){
           if(blogID == docAr[i].toObject().value("ID").toString()){
                docAr.removeAt(i);
temp = false;
           }

           if(file.open(QIODevice::WriteOnly)){
           QVariantMap map;
           map.insert("ID", blogID);
           map.insert("Title", blogTitle);
           map.insert("Main", blogMain);
           map.insert("Time", time_string);
           QJsonObject adding = QJsonObject::fromVariantMap(map);
           doc.setArray(docAr);


           }
           file.write("{\"blogg\":"+doc.toJson()+"}");
           file.close();
           ui->textEdit->clear();
           ui->textEdit_3->clear();
           ui->textEdit_2->clear();
    }
        if(temp==false){
            QMessageBox::information(this,"Information","You successfully delete your blog");
        }
        else{


                QMessageBox::warning(this,"Information","There is no such a blog to delete");
                ui->textEdit->clear();
                ui->textEdit_3->clear();
                ui->textEdit_2->clear();

            }
        }
  }
 }


void UserWindow::GetID(QString gettingID){

    ui->userIDLabel->setText("User ID: " + gettingID);
}
void UserWindow::GetEmail(QString gettingEmail){

    ui->userEmailLabel->setText("User Email: " + gettingEmail);
}

void UserWindow::on_actionDelete_2_hovered()
{
     QString blogID = ui->textEdit->toPlainText();
    if(blogID.isEmpty()){
        ui->actionDelete_2->setEnabled(false);
    }
    else{
        ui->actionDelete_2->setEnabled(true);
    }
}


void UserWindow::on_actionClear_Title_hovered()
{
    QString blogTitle = ui->textEdit_3->toPlainText();
   if(blogTitle.isEmpty()){
       ui->actionClear_Title->setEnabled(false);
   }
   else{
       ui->actionClear_Title->setEnabled(true);
   }
}


void UserWindow::on_actionClear_Blog_content_hovered()
{
    QString blogMain = ui->textEdit_2->toPlainText();
   if(blogMain.isEmpty()){
       ui->actionClear_Blog_content->setEnabled(false);
   }
   else{
       ui->actionClear_Blog_content->setEnabled(true);
   }
}



void UserWindow::on_actionClear_blog_ID_hovered()
{
    QString blogID = ui->textEdit->toPlainText();
   if(blogID.isEmpty()){
       ui->actionClear_blog_ID->setEnabled(false);
   }
   else{
       ui->actionClear_blog_ID->setEnabled(true);
   }
}


void UserWindow::on_actionClear_all_hovered()
{
    QString blogID = ui->textEdit->toPlainText();
    QString blogMain = ui->textEdit_2->toPlainText();
     QString blogTitle = ui->textEdit_3->toPlainText();
   if(blogID.isEmpty() && blogMain.isEmpty() && blogTitle.isEmpty()){
       ui->actionClear_all->setEnabled(false);
   }
   else{
       ui->actionClear_all->setEnabled(true);
   }
}

