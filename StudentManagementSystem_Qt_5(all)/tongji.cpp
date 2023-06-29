#include "tongji.h"
#include "ui_tongji.h"
#include<QMessageBox>
#include<QFile>
#include<QVBoxLayout>

tongji::tongji(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tongji)
{
    ui->setupUi(this);
}

tongji::~tongji()
{
    delete ui;
}

void tongji::on_pushButton_clicked()
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
    int n1=0,n2=0,n3=0,n4=0,n5=0,n6=0;
    for(int i=0;i<=30;i++){
        if(arr[i].avg<=250){
            n1++;

        }
        if(arr[i].avg>250&&arr[i].avg<=260){
            n2++;

        }
        if(arr[i].avg>260&&arr[i].avg<=270){
            n3++;

        }
        if(arr[i].avg>270&&arr[i].avg<=280){
            n4++;

        }
        if(arr[i].avg>280&&arr[i].avg<=290){
            n5++;
            }
        if(arr[i].avg>290&&arr[i].avg<=300){
            n6++;

        }

    }
    QBarSet *set1 = new QBarSet("个数");
    *set1 << n1 << n2 << n3 << n4 << n5 << n6 ;
    QBarSeries *series1 = new QBarSeries();
    series1->append(set1);
    QChart *chart = new QChart();
    chart->addSeries(series1);
    chart->setTitle("坐标数量"); // 设置图表的标题
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QStringList categories;
    categories << "<=250" << "250-260" << "260-270" << "270-280" << "280-290" << "290-300";
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series1);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    //ui->widget->layout()->addWidget(chartView);
    QVBoxLayout *layout = new QVBoxLayout(ui->widget);
    layout->addWidget(chartView);

}

