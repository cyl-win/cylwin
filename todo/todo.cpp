#include "todo.h"
#include "ui_todo.h"
#include <QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QMessageBox>
todo::todo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::todo)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::database();
    connect(ui->S_btn,&QPushButton::clicked,this,&todo::Sent_Widget);
    ui->S_btn->hide();

}
int m_id=0;
void todo::receiveS_btn()
{
    //发出信号
    emit Sent_Widget();

}
todo::~todo()
{
    delete ui;
}
int todo::receiveString(int id)
{
    m_id=id;
    return id;
}
void todo::on_pushButton_clicked()
{

    QString jihua=ui->lineEdit->text();
    QString time=ui->lineEdit_2->text();

    QSqlQuery query;
    query.prepare("insert into content(nr, ddl,cid) values (?, ?, ? )");
    query.addBindValue(jihua);
    query.addBindValue(time);
    query.addBindValue(m_id);
    query.exec();
    QMessageBox::information(this,"infor","添加成功");
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}


void todo::on_pushButton_2_clicked()
{
    QString time=ui->lineEdit_3->text();
    QSqlQuery query;
    query.prepare("select nr from content where ddl= ?") ;
    query.addBindValue(time);
    if (query.exec()) {
        ui->listWidget->clear();
        while (query.next()) {
            QString drContent = query.value(0).toString();
            QListWidgetItem* item = new QListWidgetItem(drContent);
            ui->listWidget->addItem(item);
        }
    } else {
        qDebug() << "查询失败";
    }


}


void todo::on_pushButton_3_clicked()
{
    QSqlQuery query;
    query.prepare("select nr from content where cid= ? ") ;
    query.addBindValue(m_id);
    if (query.exec()) {
        ui->listWidget->clear();
        while (query.next()) {
            QString drContent = query.value(0).toString();
            QListWidgetItem* item = new QListWidgetItem(drContent);
            ui->listWidget_2->addItem(item);
        }
    } else {
        qDebug() << "查询失败";
    }
}

