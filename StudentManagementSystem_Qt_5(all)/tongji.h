#ifndef TONGJI_H
#define TONGJI_H

#include <QDialog>
#include<studentinfo.h>
#include <QDialog>
#include <QtCharts/QBarSeries>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QMainWindow>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include<QLayout>
namespace Ui {
class tongji;
}

class tongji : public QDialog
{
    Q_OBJECT

signals:
    void display(int number);

public:
    explicit tongji(QWidget *parent = nullptr);
    ~tongji();
    QBarSet *set1;
    QBarSeries *series1;

private slots:
    void on_pushButton_clicked();

private:
    Ui::tongji *ui;
};

#endif // TONGJI_H
