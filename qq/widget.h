#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QUdpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
     Widget(QWidget *parent ,QString name);
    void closeEvent(QCloseEvent *);
    ~Widget();
    enum Msgtype{Msg,Userenter,Userleft};
    void sedmsg(Msgtype type);
    QString getname();
    QString getmsg();
    void userenter(QString username);
    void userleft(QString username,QString time);
    void receivemessage();

signals:
    void closeWidget();
private:
    Ui::Widget *ui;
    quint16 port;
    QString uname;
    QUdpSocket *udpSocket;
};
#endif // WIDGET_H
