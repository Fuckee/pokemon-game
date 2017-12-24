#ifndef SERVER_H
#define SERVER_H
#include<QObject>
#include"socket.h"
#include<QTcpServer>
#include<QListWidget>
class QLabel;
class server : public QTcpServer
{
    Q_OBJECT
public:
    server(QObject* parent=0);
    QList<Socket*> SocketList;//用来保存与每一个客户端连接的tcpclientsocket
protected:
    void incomingConnection(int socketDescriptor);
signals:
    void new_connect();//有一个申请连接
    void new_connect_success(QString);//申请成功
    void show_connect_stop(QString);//有一个连接中断
public slots:
    void connect_success(QString,QString,Socket*);
    void connect_stop(int,QString);//有一个连接中断
private:
    int index;
};

#endif // SERVER_H
