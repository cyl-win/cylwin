#include "widget.h"
#include "ui_widget.h"
#include<QDataStream>
#include<QMessageBox>
#include<QDateTime>
#include<QDataStream>
#include<QMessageBox>
#include<QDateTime>
#include<QTableWidget>
#include<QComboBox>
#include<QFont>
#include<QColorDialog>
#include<QFileDialog>
#include<QDebug>
Widget::Widget(QWidget *parent,QString name)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->uname=name;

    this->port=9999;
    this->udpSocket=new QUdpSocket(this);
    udpSocket->bind(port,QUdpSocket::ShareAddress|QUdpSocket::ReuseAddressHint);
    connect(udpSocket,&QUdpSocket::readyRead,this,&Widget::receivemessage);
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        sedmsg(Msg);
    });
    connect(ui->pushButton_2,&QPushButton::clicked,this,[=](){
        this->close();
    });
    connect(ui->fontComboBox,&QFontComboBox::currentFontChanged,this,[=](const QFont &font){

        ui->textBrowser->setFontFamily(font.toString());
        ui->textBrowser->setFocus();
    });
    void (QComboBox:: *sizeBtn)(const QString &text)=&QComboBox::currentTextChanged;
    connect(ui->comboBox,sizeBtn,this,[=](const QString &text){
        ui->textBrowser->setFontPointSize(text.toDouble());
        ui->textBrowser->setFocus();
    });
    sedmsg(Userenter);

    connect(ui->toolButton_6,&QToolButton::clicked,this,[=](bool checked){

        if(checked){
            ui->textBrowser->setFontWeight(QFont::Bold);
        }else{
            ui->textBrowser->setFontWeight(QFont::Normal);
        }
    });


    connect(ui->toolButton_4,&QToolButton::clicked,this,[=](bool checked){
        ui->textBrowser->setFontItalic(checked);
        ui->textBrowser->setFocus();
    });


    connect(ui->toolButton,&QToolButton::clicked,this,[=](bool checked){
        ui->textBrowser->setFontUnderline(checked);
        ui->textBrowser->setFocus();
    });


    connect(ui->toolButton_5,&QToolButton::clicked,this,[=](){
        ui->textBrowser->clear();
    });


    connect(ui->toolButton_3,&QToolButton::clicked,this,[=](){
        QColor color=QColorDialog::getColor(color,this);
        ui->textBrowser->setTextColor(color);
    });


    connect(ui->toolButton_4,&QToolButton::clicked,this,[=](){
        if(ui->textBrowser->toPlainText().isEmpty()){
            QMessageBox::warning(this,"警告","保存内容不能为空");
            return;
        }

        QString fileName=QFileDialog::getSaveFileName(this,"保存聊天记录","聊天记录","(*.txt)");
        if(!fileName.isEmpty()){
            QFile file(fileName);
            file.open(QIODevice::WriteOnly|QFile::Text);
            QTextStream stream(&file);
            stream<<ui->textBrowser->toPlainText();
            file.close();
        }
    });
}

void Widget::closeEvent(QCloseEvent *)
{
    emit closeWidget();
    sedmsg(Userleft);
    udpSocket->close();
    udpSocket->destroyed();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::sedmsg(Msgtype type)
{
    QByteArray array;
    QDataStream stream(&array,QIODevice::WriteOnly);
    stream<<type<<this->getname();
    switch (type) {
    case Msg:
        if(ui->textEdit->toPlainText()==""){
            QMessageBox::warning(this,"warning","不能为空");
            return;
        }
        stream<<this->getmsg();
        break;
    case Userenter:
        break;
    case Userleft:
        break;
    }
    udpSocket->writeDatagram(array.data(),array.size(),QHostAddress::Broadcast,this->port);

}

QString Widget::getname()
{
    return uname;
}

QString Widget::getmsg()
{
    QString msg=ui->textEdit->toHtml();
    ui->textEdit->clear();
    ui->textEdit->setFocus();
    return msg;
}

void Widget::receivemessage()
{
    qint64 size=udpSocket->pendingDatagramSize();

    QByteArray *array=new QByteArray(size,0);
    udpSocket->readDatagram(array->data(),size);
    QDataStream stream(array,QIODevice::ReadOnly);
    int mytype = 0 ;
    QString name,msg;
    QString time=QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    stream>>mytype;
    switch (mytype) {
    case Msg:
        stream>>name>>msg;
        ui->textBrowser->setTextColor(QColor(Qt::gray));
        ui->textBrowser->append("["+name+"]"+time);
        ui->textBrowser->append(msg);
        break;
    case Userenter:
        stream>>name;
        userenter(name);
        break;
    case Userleft:
        stream>>name;
        userleft(name,time);
        break;

    }

}
void Widget::userenter(QString username)
{
    bool IsEmpty=ui->tableWidget->findItems(username,Qt::MatchExactly).isEmpty();
       if(IsEmpty)
       {
           QTableWidgetItem *table=new QTableWidgetItem(username);
           ui->tableWidget->insertRow(0);
           ui->tableWidget->setItem(0,0,table);
           ui->textBrowser->setTextColor(QColor(Qt::gray));
           ui->textBrowser->append(username+"已上线");
           ui->label->setText(QString("在线人数:%1").arg(ui->tableWidget->rowCount()));
           sedmsg(Userenter);
       }
}
void Widget::userleft(QString username, QString time)
{
    bool isEmpty=ui->tableWidget->findItems(username,Qt::MatchExactly).isEmpty();
    if(!isEmpty){
        int row=ui->tableWidget->findItems(username,Qt::MatchExactly).first()->row();
        ui->tableWidget->removeRow(row);
        ui->textBrowser->append(username+"用户于"+time+"离开");
         ui->label->setText(QString("在线人数:%1").arg(ui->tableWidget->rowCount()));
    }
}


