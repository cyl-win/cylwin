#ifndef TODO_H
#define TODO_H

#include <QDialog>

namespace Ui {
class todo;
}

class todo : public QDialog
{
    Q_OBJECT

public:
    explicit todo(QWidget *parent = nullptr);
    ~todo();


signals:
    void Sent_Widget();
public slots:
    int receiveString(int str);
public slots:
    void receiveS_btn();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::todo *ui;

};

#endif // TODO_H
