#ifndef SEARCHNOCLEAR_H
#define SEARCHNOCLEAR_H
#include <QMessageBox>
#include <QDialog>
#include "studentinfo.h"
namespace Ui {
class searchnoclear;
}

class searchnoclear : public QDialog
{
    Q_OBJECT

public:
    explicit searchnoclear(QWidget *parent = nullptr);
    ~searchnoclear();


private slots:
    void on_noclear_clicked();
signals:
    void display(int number);
private:
    Ui::searchnoclear *ui;

};

#endif // SEARCHNOCLEAR_H
