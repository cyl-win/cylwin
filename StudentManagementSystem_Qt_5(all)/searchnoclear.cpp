#include "searchnoclear.h"
#include "ui_searchnoclear.h"
#include <QFile>
#include<QString>
searchnoclear::searchnoclear(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchnoclear)
{
    ui->setupUi(this);
}

searchnoclear::~searchnoclear()
{
    delete ui;
}

void searchnoclear::on_noclear_clicked()
{
    if(ui->lineEdit->text()==" "){
        QMessageBox::about(NULL, "反馈", "id不能为空");
        return;
    }
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

    QString name1=ui->lineEdit->text();
    for(int i=0;i<m_size;i++){
        int ret1=arr[i].name.indexOf(name1);
        if(ret1!=-1){
            ui->label_7->setText((arr[i].id));
            ui->label_8->setText(QString::number(arr[i].math));
            ui->label_9->setText(QString::number(arr[1].english));
            ui->label_10->setText(QString::number(arr[m_size].languageC));
            ui->label_11->setText(QString::number(arr[i].avg));
        }
    }
//    QVector<StudentInfo> allStudentInfo;
//    while(!inp.atEnd()){ //读到文件结尾
//        QString name;
//        int id, math, english, languageC;
//        inp >> name >> id >> math >> english >> languageC;
//        allStudentInfo.push_back(StudentInfo(name, id, math, english, languageC));
//        //调用之前建立的构造函数实例化一个StudentInfo对象并将其加入allStudentInfo
//        allStudentInfo.pop_back();
//        //扔掉最后的无用数据
//        file.close();
//        //关闭文件
//        QString name1=ui->lineEdit->text();
//        bool flag=false;
//        int ret1;
//        for(auto i : allStudentInfo){
//            ret1=allStudentInfo.indexOf(name1);
//            if(ret1!=-1){
//                ui->label_7->setText(i.getName());
//                ui->label_8->setText(QString::number(i.getMath()));
//                ui->label_9->setText(QString::number(i.getEnglish()));
//                ui->label_10->setText(QString::number(i.getLanguageC()));
//                ui->label_11->setText(QString::number(i.getAvg()));
//                flag = true;
//                break;
//            }
//        }
//        if(!flag){
//            QMessageBox::about(NULL, "反馈", "id不存在！");
//        }
//        ui->lineEdit->clear();
//    }

    }


