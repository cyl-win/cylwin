#ifndef FENXI_H
#define FENXI_H

#include <QDialog>
#include "studentinfo.h"
namespace Ui {
class fenxi;
}

class fenxi : public QDialog
{
    Q_OBJECT

public:
    explicit fenxi(QWidget *parent = nullptr);
    ~fenxi();

signals:
    void display(int number);

private slots:
    void on_start_clicked();

private:
    Ui::fenxi *ui;
};

#endif // FENXI_H
