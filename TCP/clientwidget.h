#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include<QTcpSocket>
namespace Ui {
class clientwidget;
}

class clientwidget : public QWidget
{
    Q_OBJECT

public:
    explicit clientwidget(QWidget *parent = nullptr);
    ~clientwidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::clientwidget *ui;
    QTcpSocket *tcpsocket1;
};

#endif // CLIENTWIDGET_H
