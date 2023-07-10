#ifndef USERWINDOW_H
#define USERWINDOW_H
#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonParseError>
#include <QFile>
#include <QFileDialog>
#include <QStandardItem>
#include <QMessageBox>
#include <QTextStream>
#include <QDialog>
#include <QTimer>
#include <QDateTime>
#include "dialog.h"

class MainWindow;

namespace Ui {
class UserWindow;
}

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(QWidget *parent = nullptr);
    ~UserWindow();
    QJsonDocument doc;
    QJsonParseError docError;
    QString globPath;
    QJsonArray docAr;
    QFile file;

private slots:

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_actionClear_Title_triggered();

    void on_actionClear_Blog_content_triggered();

    void on_actionClear_blog_ID_triggered();

    void on_actionClear_all_triggered();

    void on_actionShow_all_blogs_triggered();

    void on_actionDelete_2_triggered();

    void GetID(QString);
    void GetEmail(QString);

    void on_actionDelete_2_hovered();


    void on_actionClear_Title_hovered();

    void on_actionClear_Blog_content_hovered();

    void on_actionClear_blog_ID_hovered();

    void on_actionClear_all_hovered();

private:
    Ui::UserWindow *ui;
   QString usedUserID;
   QString userEmail;
   MainWindow *w;
   Dialog *dialog;

};
#endif // USERWINDOW_H
