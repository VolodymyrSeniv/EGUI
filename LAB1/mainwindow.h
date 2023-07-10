#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>
#include <QObject>
#include <QFileDialog>
#include <QStandardItem>
#include <QMessageBox>
#include <QTextStream>
#include <QWidget>
#include "dialog.h"
#include "userwindow.h"


class UserWindow;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{

    Q_OBJECT
friend class UserWindow;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
void Someranodmmethod();
    QJsonDocument doc;
    QJsonArray docAr;
    QJsonParseError docError;
    QFile file;
    //QString selectedID;
    //QString selectedEmail;
    QDir current;
    void setId(QString someID);
    QString getId();
    void setEmail(QString someEmail);
    QString getEmail();



private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
signals:
    void SendID(QString);
    void SendEmail(QString);

private:
    Ui::MainWindow *ui;
    //Dialog *secondWindow;
    QString selectedID;
    QString selectedEmail;
    UserWindow *userWindow;
};
#endif // MAINWINDOW_H
