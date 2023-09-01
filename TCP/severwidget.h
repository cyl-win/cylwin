#ifndef SEVERWIDGET_H
#define SEVERWIDGET_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class severWidget; }
QT_END_NAMESPACE

class severWidget : public QWidget
{
    Q_OBJECT

public:
    severWidget(QWidget *parent = nullptr);
    ~severWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::severWidget *ui;
    QTcpServer *tcpsever;//监听
    QTcpSocket *tcpsocket;//通信

};
#endif // SEVERWIDGET_H
