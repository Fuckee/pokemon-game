#ifndef WIDGET_H
#define WIDGET_H
#include"blurpicker/blurpicker.h"
#include <QWidget>
#include<QTcpSocket>
#include<QMap>
#include"theshare.h"
#include<QTimer>
#include"regist.h"
namespace Ui {
class Widget;
}
QT_BEGIN_NAMESPACE
class QString;
class QLineEdit;
class QLabel;
class QPushButton;
class QGridLayout;
QT_END_NAMESPACE
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void toRead();//socket中有数据读取
    void sendRequest();//发送账号密码
    void toConnect();//连接服务器
    void is_Connect();
    void closeConnection();\
    void haveError();
    static void askForOnline();//所有咨询
    void askForOtherPoke(int i);
    void askForOther();
    static void askOnlineagain();//再次请求在线用户以及对方精灵
    static void returnMyInformation();//return user info
    static void returnMyPoke();//return user poke to the server
    static void askForAllUser();//ask all people
    void askForOtherAgain();//再次请求在线用户的精灵
    void askForOtherPokeAgain(int i);
    void askForMyInfo();
    void goForGame();
    void registNew(QString,QString);
    void networkGreat();
 public:
    void askForMy();
    QTimer* Timer;
 signals:
    void connect_Ready();
    void to_ask_next(int);
private slots:
    void on_regist_clicked();

private:
    Ui::Widget *ui;
    bool state;
    quint16 nextBlockSize;
    bool hasRegist;
};

#endif // WIDGET_H
