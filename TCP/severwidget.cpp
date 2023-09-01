#include "severwidget.h"
#include "ui_severwidget.h"
#include <QHostAddress>
severWidget::severWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::severWidget)
{
    ui->setupUi(this);
    tcpsever=new QTcpServer(this);
    this->setWindowTitle("客户端:8888");
    tcpsever=NULL;
    tcpsocket=NULL;
    const QHostAddress &address = QHostAddress::Any;
    //tcpsever->listen(QHostAddress::Any,8000);
    connect(tcpsever,&QTcpServer::newConnection,[=](){
        tcpsocket=tcpsever->nextPendingConnection();//取出建立好连接的套接字
        QString Ip=tcpsocket->peerAddress().toString();
        quint16 port=tcpsocket->peerPort();
        QString temp=QString("[%1:%2]:成功连接").arg(Ip).arg(port);
        ui->textEditRead->setText(temp);

        connect(tcpsocket,&QTcpSocket::readyRead,[=](){
        QByteArray array=tcpsocket->readAll();
        ui->textEditRead->append(array);
        });
    });


}

severWidget::~severWidget()
{
    delete ui;
}


void severWidget::on_pushButton_clicked()
{
    if(NULL==tcpsocket){
        return;
    }
    QString str=ui->textEditWrite->toPlainText();

    tcpsocket->write(str.toUtf8().data());
}


void severWidget::on_pushButton_2_clicked()
{
    if(NULL==tcpsocket){
        return;
    }
    tcpsocket->disconnectFromHost();
    tcpsocket->close();
    tcpsocket=NULL;
}

