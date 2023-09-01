#ifndef ZHUCE_H
#define ZHUCE_H

#include <QDialog>

namespace Ui {
class zhuce;
}

class zhuce : public QDialog
{
    Q_OBJECT

public:
    explicit zhuce(QWidget *parent = nullptr);
    ~zhuce();
    bool flag=0;
signals:
    void Sent_Widget();

public slots:
    void receiveS_btn();
private slots:
    void on_pushButton_clicked();

private:
    Ui::zhuce *ui;
};

#endif // ZHUCE_H
