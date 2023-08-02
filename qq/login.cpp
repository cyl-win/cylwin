#include "login.h"
#include "ui_login.h"
#include<QIcon>
#include <QVector>
#include <QPixmap>
#include<QList>
#include <QToolButton>
#include<QMessageBox>
#include"widget.h"
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/new/prefix1/t9.jpg"));
    this->setWindowTitle("my qq");
    QList<QString> namelist;
    namelist<<"crime"<<"dreamboat"<<"lgrid"<<"cylwin"<<"yunyancy"<<"small l"<<"cylsuc";
    QStringList iconNamelist;
    QVector<QToolButton*> vector;
    iconNamelist<<"t1"<<"t2"<<"t3"<<"t4"<<"t5"<<"t6"<<"t8";
    for (int i = 0; i < 7; ++i) {
        QToolButton *btn=new QToolButton(this);
        btn->setIcon(QPixmap(QString(":/new/prefix1/%1.jpg").arg(iconNamelist[i])));
        btn->setIconSize(QSize(10,50));
        btn->setText(QString("%1").arg(namelist[i]));
        btn->setAutoRaise(true);
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        ui->vlayout->addWidget(btn);
        vector.push_back(btn);
        isuse.push_back(false);
    }
    for(int i=0;i<7;i++){
        connect(vector[i],&QToolButton::clicked,[=](){
            if(isuse[i]){
                QMessageBox::warning(this,"warning","已经打开");
                return;
            }
            isuse[i]=true;
            Widget *widget=new Widget(nullptr,vector[i]->text());
            widget->setWindowIcon(vector[i]->icon());
            widget->setWindowTitle(vector[i]->text());
            widget->show();
            connect(widget,&Widget::closeWidget,[=](){
                isuse[i]=false;
                            });
        });
    }

}

login::~login()
{
    delete ui;
}
