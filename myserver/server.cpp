#include "server.h"
#include"socket.h"
#include<QMessageBox>
server::server(QObject *parent):QTcpServer(parent)
{
    listen(QHostAddress::Any,8086);
    index=1;
}

void server::incomingConnection(int socketDescriptor)
{
    emit new_connect();
    Socket *socket=new Socket(this,index);//创建一个新的套接字与客户端通信
    index++;
    socket->setSocketDescriptor(socketDescriptor);//将套接字描述符制定为参数socketDescriptpr
    qDebug()<<socketDescriptor;
    connect(socket,SIGNAL(connect_success(QString,QString,Socket*)),this,SLOT(connect_success(QString,QString,Socket*)));
    connect(socket,SIGNAL(stopConnect(int,QString)),this,SLOT(connect_stop(int,QString)));

}
void server::connect_stop(int descriptor,QString id)
{
    emit show_connect_stop(id);
    for(int i=0;i<SocketList.count();i++)
    {
        Socket* item=SocketList.at(i);
        if(item->socketDescriptor()==descriptor)
        {
            SocketList.removeAt(i);
            item->deleteLater();
            return;
        }
    }
    return;
}

void server::connect_success(QString id, QString pw,Socket* socket)
{
    emit new_connect_success(id);
    socket->set_index(SocketList.count());
    SocketList.append(socket);//将套接字加入客户端套接字列表以便管理
}


