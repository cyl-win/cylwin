#include "zhuce.h"
#include "ui_zhuce.h"
#include <QMessageBox>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>
zhuce::zhuce(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::zhuce)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::database();
    connect(ui->pushButton_2,&QPushButton::clicked,this,&zhuce::Sent_Widget);
}

void zhuce::receiveS_btn()
{
    //发出信号
    emit Sent_Widget();

}
zhuce::~zhuce()
{
    delete ui;
}

void zhuce::on_pushButton_clicked()
{
    QString username=ui->lineEdit->text();
    QString pas1=ui->lineEdit_2->text();
    QString pas2=ui->lineEdit_3->text();
    QString queryStr = QString("SELECT * FROM account WHERE username='%1'")
                           .arg(username);
    QSqlQuery query;
    if(pas1==pas2){
        if (query.exec(queryStr) && query.next()){
            QMessageBox::information(this,"infor","用户名已经存在");
        }
        else{
            flag=1;
            QMessageBox::information(this,"infor","可以注册");
        }
    }
    else {
        QMessageBox::information(this,"infor","两次输入的密码不一致");
    }
    if(flag==1){
//        QString queryStr2 = QString("INSERT INTO account (username, password) VALUES ('%1', '%2')")
//                               .arg(username)
//                               .arg(pas1);
//        QSqlDatabase::database().commit();
        query.prepare("insert into account(username, password) values (?, ?)");
        query.addBindValue(username);
        query.addBindValue(pas1);
        query.exec();


    }
    QSqlQuery query2;
    if (query2.exec(queryStr)) {
        qDebug()<<username<<pas1;

    } else {
        qDebug()<<2;

    }
}

