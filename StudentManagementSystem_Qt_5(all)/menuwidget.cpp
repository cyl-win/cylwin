#include "menuwidget.h"
#include "ui_menuwidget.h"
#include <QImage>
#include <QPalette>
#include <QFrame>
MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuWidget)
{
    ui->setupUi(this);
    this->setStyleSheet("QFrame{background-image:url(:/1.jpg)}");
}

MenuWidget::~MenuWidget()
{
    delete ui;
}

void MenuWidget::on_addButton_clicked(){
    emit display(1);    //id为1的是addstudentwidget
}
void MenuWidget::on_selectButton_clicked(){
    emit display(2);    //id为2的是selectwidget
}

void MenuWidget::on_modifyButton_clicked(){
    emit display(3);    //id为3的是modifywidget
}

void MenuWidget::on_sortButton_clicked(){
    emit display(4);    //id为4的是sortwidget
}

void MenuWidget::on_exitButton_clicked(){
    QApplication::exit();   //退出
}

void MenuWidget::on_pushButton_2_clicked()
{
    emit display(5);
}


void MenuWidget::on_fenxi_clicked()
{
    emit display(6);
}


void MenuWidget::on_pushButton_clicked()
{
    emit display(7);
}

