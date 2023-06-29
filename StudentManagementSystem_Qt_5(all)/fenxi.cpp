#include "fenxi.h"
#include "ui_fenxi.h"
#include <QFile>
#include <QString>
#include<QMessageBox>
#include<QDebug>
fenxi::fenxi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fenxi)
{
    ui->setupUi(this);
}

fenxi::~fenxi()
{
    delete ui;
}


void fenxi::on_start_clicked()
{
    QFile file("D:\\QT\\StudentManagerSystem\\1.txt");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    if(!file.isOpen()){ //文件打开失败
        QMessageBox::about(NULL, "反馈", "文件打开失败");
        return;
    }

    QTextStream inp(&file);
    StudentInfo arr[10000];
    QFile file1("D:\\QT\\StudentManagerSystem\\1.txt");
    file1.open(QIODevice::ReadOnly);
    QTextStream in(&file1);
    int m_size=0;
    while(!in.atEnd()){
        in>>arr[m_size].name>>arr[m_size].id>>arr[m_size].math>>arr[m_size].english>>arr[m_size].languageC;
        arr[m_size].avg=arr[m_size].math+arr[m_size].english+arr[m_size].languageC;
        m_size++;
    }
    m_size--;
    file.close();
    int mathavr1=0,mathavr=0;
    int wuliavr1=0,wuliavr=0;
    int cavr1=0,cavr=0;
    int avr=0,avr1=0;
    //qDebug()<<arr[28].math;
    for(int i=0;i<m_size;i++){
        mathavr1=mathavr1+arr[i].math;
        wuliavr1=wuliavr1+arr[i].english;
        cavr1=cavr1+arr[i].languageC;
        avr1=avr1+arr[i].avg;
        //qDebug()<< mathavr1;
        //qDebug()<<arr[i].math;
    }
    mathavr=(mathavr1)/29;
    wuliavr=(wuliavr1)/29;
    cavr=(cavr1)/29;
    avr=(avr1)/29;
    ui->mathavr->setText(QString::number(mathavr));
    ui->wuliavr->setText(QString::number(wuliavr));
    ui->Cavr->setText(QString::number(cavr));
    ui->avr->setText(QString::number(avr));
    int mathjg=0,ejg=0,cjg=0;
    for(int j=0;j<m_size;j++){
        if(arr[j].math>=60){
            mathjg=mathjg+1;
        }
        if(arr[j].english>=60){
            ejg=ejg+1;
        }
        if(arr[j].languageC>=60){
            cjg=cjg+1;
        }
    }
    mathjg=mathjg/28;
    ejg=ejg/28;
    cjg=cjg/28;
    ui->mathjg->setText(QString::number(mathjg));
    ui->wulijg->setText(QString::number(ejg));
    ui->Cjg->setText(QString::number(cjg));
}

