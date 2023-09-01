#include "clientwidget.h"
#include "ui_clientwidget.h"
#include <QHostAddress>
clientwidget::clientwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::clientwidget)
{
    ui->setupUi(this);
    tcpsocket1=NULL;
    tcpsocket1=new QTcpSocket(this);


}

clientwidget::~clientwidget()
{
    delete ui;
    delete tcpsocket1;
}

void clientwidget::on_pushButton_clicked()
{
    qint16 port=ui->lineEditport->text().toInt();
    QString Ip=ui->lineEditIp->text();


    tcpsocket1->connectToHost(QHostAddress(Ip),port);
}

