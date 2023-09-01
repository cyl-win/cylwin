#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include "zhuce.h"
#include <QDebug>
#include <QMessageBox>
#include "todo.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool login=false;
    bool appear=false;
    //todo ToDo;
signals:
    void stringPassed(int str);

private slots:
    void on_pushButton_clicked();

    void on_checkBox_clicked();


private:
    void ChangeWindow();
    zhuce SEC;
    void DealSent();
    void ChangeWindow2();
    todo SEC2;
    void DealSent2();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
