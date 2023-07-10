#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}



Dialog::~Dialog()
{
    delete ui;
}



void Dialog::on_pushButton_clicked()
{
    QFile file("jsn.json");
    if(file.open(QIODevice::ReadOnly|QIODevice::Text)){
        doc = QJsonDocument::fromJson(QByteArray(file.readAll()),&docError);
        file.close();

        if(docError.errorString().toInt()==QJsonParseError::NoError){
            QStandardItemModel* model = new QStandardItemModel(nullptr);
            model->setHorizontalHeaderLabels(QStringList()<<"ID"<<"Title");

            docAr = QJsonValue(doc.object().value("blogg")).toArray();

            for(int i = 0; i < docAr.count(); i ++){
                QStandardItem* item1 = new QStandardItem(docAr.at(i).toObject().value("ID").toString());
                QStandardItem* item2 = new QStandardItem(docAr.at(i).toObject().value("Title").toString());
                model->appendRow(QList<QStandardItem*>()<<item1<<item2);


            }
       ui->tableView->setModel(model);
        }
    }
    else{
        QMessageBox::information(this,"Error","File didn't open");
        return;
    }

}

