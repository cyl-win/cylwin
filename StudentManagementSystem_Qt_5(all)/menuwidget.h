#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>

namespace Ui {
class MenuWidget;
}

class MenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MenuWidget(QWidget *parent = nullptr);
    ~MenuWidget();

private:
    Ui::MenuWidget *ui;

signals:
    void display(int number);

private slots:
    void on_addButton_clicked();
    void on_selectButton_clicked();
    void on_modifyButton_clicked();
    void on_sortButton_clicked();
    void on_exitButton_clicked();

    void on_pushButton_2_clicked();
    void on_fenxi_clicked();
    void on_pushButton_clicked();
};

#endif // MENUWIDGET_H
