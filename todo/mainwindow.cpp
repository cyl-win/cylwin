#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include<QSqlQuery>
#include<QString>
#include <QStackedLayout>
#include <QStackedWidget>
#include<QSqlDatabase>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("mysql"); //不是Database,记得别填错
    db.setUserName("cylwin");
    db.setPassword("CYL20040806");
    bool ok = db.open();
    if (ok){
        QMessageBox::information(this, "infor", "link success");
    }
    else {
        QMessageBox::information(this, "infor", "link failed");
        qDebug()<<"error open database because"<<db.lastError().text();
    }
    QSqlQuery query;
    query.exec("CREATE TABLE account( "
               "id INT PRIMARY KEY AUTO_INCREMENT, "
               "username VARCHAR(20), "
               "password VARCHAR(20))");
    query.exec("CREATE TABLE content( "
               "nr varchar(20), "
               "ddl VARCHAR(20), "
               "cid int,"
               "constraint FK_connect foreign key(cid) references account(id))");
    connect(ui->pushButton_2,&QPushButton::released,this,&MainWindow::ChangeWindow);
    connect(&SEC,&zhuce::Sent_Widget,this,&MainWindow::DealSent);
    connect(ui->pushButton,&QPushButton::released,this,&MainWindow::ChangeWindow2);
    connect(&SEC2,&todo::Sent_Widget,this,&MainWindow::DealSent2);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    if(appear){
        ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    }
    todo *Tod = new todo();
    connect(this, SIGNAL(stringPassed(int)), Tod, SLOT(receiveString(int)));

}

void MainWindow::ChangeWindow()
{
    //隐藏自己窗口
    this->hide();
    //显示second窗口
    SEC.show();


}
void MainWindow::ChangeWindow2()
{
    //隐藏自己窗口
    if(login==false){
    this->hide();
    //显示second窗口
    SEC2.show();}


}
void MainWindow:: DealSent()
{
    this->show();
    SEC.hide();
}
void MainWindow:: DealSent2()
{
    this->show();
    SEC2.hide();
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString username=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();
    QString queryStr = QString("SELECT * FROM account WHERE username='%1' AND password='%2'")
                           .arg(username)
                           .arg(password);

    QSqlQuery query;
    if (query.exec(queryStr) && query.next()) {
        login=true;
        QMessageBox::information(this,"infor","登陆成功");
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        query.prepare("SELECT id FROM account WHERE username = :username AND password = :password");
        query.bindValue(":username", username);
        query.bindValue(":password", password);
        if (query.exec() && query.next()) {
            int userId23 = query.value(0).toInt();
            emit stringPassed(userId23);


        }
    } else {
         QMessageBox::information(this, "infor", "账号或密码错误");
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        SEC2.hide();
        this->show();
    }



}


void MainWindow::on_checkBox_clicked()
{
    appear=true;
    if(appear){
         ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    }
}

