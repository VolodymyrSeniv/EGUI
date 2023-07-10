#ifndef DIALOG_H
#define DIALOG_H
#include <QDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>
#include <QFileDialog>
#include <QStandardItem>
#include <QMessageBox>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog{
    Q_OBJECT

    QJsonDocument doc;
    QJsonArray docAr;
    QJsonParseError docError;

public:
    explicit Dialog(QWidget *parent = nullptr);

    ~Dialog();

private slots:


    void on_pushButton_clicked();

private:

    Ui::Dialog *ui;
};

#endif // DIALOG_H
