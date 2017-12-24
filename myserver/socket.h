#ifndef SOCKET_H
#define SOCKET_H

#include"player.h"
#include<QObject>
#include<QTcpSocket>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMap>
#include<pokemon/type.h>
#include<pokemon/all_head.h>
class Socket : public QTcpSocket//TCP套接字
{
    Q_OBJECT   //实现信号与槽的通信
public:
    Socket(QObject *parent=0,int number=0);
    void sendMessage(quint8 type,QString="");
    int get_index()
    {
        return _index;
    }
    void set_index(int i)
    {
        _index=i;
    }

protected slots:
    void toRead();
    void stop();
signals:
    void connect_success(QString,QString,Socket*);
    void stopConnect(int,QString);//告知服务器有一个连接中断
private:
    int state;
    quint16 nextBlockSize;
    QString _id;
    int _index;//表名是第几号连接
    int _number;//用于数据库连接
    bool check_login(QString name,QString password);
    QSqlDatabase mydb;
    QSqlQuery query;
    void returnOnline();
    void returnOnlineagain();
    void returnUserPoke();
    void returnSomeBody(QString name);
    void returnSomeBodyAgain(QString name);
    void updateUser(QString username,QList<pokemon*> list);
    void returnInfo(QString);
    QMap<QString,Poke_quality> StringtoPokeQuality;
    QMap<QString,Quality> StringtoQuality;
    QMap<Poke_quality,QString> PokeQualityToString;
    QMap<Quality,QString> QualityToString;
    void returnAllInfo(QString);
    void registNew(QString,QString);
    void updateMy(player);


};

#endif // SOCKET_H
