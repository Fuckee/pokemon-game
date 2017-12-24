#include "widget.h"
#include "ui_widget.h"
#include<QtWidgets>
#include<QTcpSocket>
#include<QHostAddress>
#include"pokemon/bulbasaur.h"
#include<QTimer>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)//实现了与服务器的socket进行数据交互的类
{
    ui->setupUi(this);
    ui->pw_edit->setEchoMode(QLineEdit::Password);
    state=false;
    connect(ui->login,SIGNAL(clicked(bool)),this,SLOT(sendRequest()));
    connect(this,SIGNAL(to_ask_next(int)),this,SLOT(askForOtherPoke(int)));
    nextBlockSize=0;
    //初始化map
    theShare::StringtoPokeQuality.insert("hpful",hpful);
    theShare::StringtoPokeQuality.insert("strong",strong);
    theShare::StringtoPokeQuality.insert("defendful",defendful);
    theShare::StringtoPokeQuality.insert("fast",fast);
    theShare::StringtoQuality.insert("excellent",excellent);
    theShare::StringtoQuality.insert("great",great);
    theShare::StringtoQuality.insert("normal",normal);
    theShare::StringtoQuality.insert("bad",bad);

    theShare::PokeQualityToString.insert(hpful,"hpful");
    theShare::PokeQualityToString.insert(strong,"strong");
    theShare::PokeQualityToString.insert(defendful,"defendful");
    theShare::PokeQualityToString.insert(fast,"fast");
    theShare::QualityToString.insert(excellent,"excellent");
    theShare::QualityToString.insert(great,"great");
    theShare::QualityToString.insert(normal,"normal");
    theShare::QualityToString.insert(bad,"bad");
    hasRegist=false;
    //初始化界面按钮
    ui->login->setEnabled(false);
    ui->regist->setEnabled(false);
    toConnect();
    //定时器，用于与服务器连接
    Timer=new QTimer(this);
    connect(Timer, SIGNAL(timeout()), this, SLOT(toConnect()));
    Timer->start(5000);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::toConnect()//与服务器进行连接
{
      theShare::socket=new QTcpSocket(this);
      theShare::socket->connectToHost(QHostAddress::LocalHost,8086);
        //ui->state_label->setText("正在尝试连接");
      connect(theShare::socket,SIGNAL(connected()),this,SLOT(networkGreat()));
      connect(theShare::socket,SIGNAL(readyRead()),this,SLOT(toRead()));
      connect(theShare::socket,SIGNAL(disconnected()),this,SLOT(closeConnection()));
      connect(theShare::socket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(haveError()));


}
void Widget::toRead()//有新的数据可以读取
{
    QDataStream in(theShare::socket);
    in.setVersion(QDataStream::Qt_5_7);

    if(nextBlockSize==0)
    {
        if(theShare::socket->bytesAvailable()<sizeof(quint16))
        {
            return;
        }
        in>>nextBlockSize;
    }
    if(theShare::socket->bytesAvailable()<nextBlockSize)
    {
        return;
    }
    if(!state)//未确定连接状态
    {
        quint8 type;
        in>>type;
        if(type=='Y')
        {
            state=true;
            ui->state_label->setText("connect sucess");
            //this->hide();
            nextBlockSize=0;

            //Timer = new QTimer(this);
            //connect(Timer, SIGNAL(timeout()), this, SLOT(gofor));
            //timer->start(1000);
            QTimer::singleShot(1000,this,SLOT(goForGame()));
            askForOnline();
            //

        }
        else if(type=='N')
        {
            ui->state_label->setText("id or password wrong");
            ui->login->setEnabled(true);
            theShare::socket->deleteLater();
            nextBlockSize=0;

        }
        else if(type=='P')//注册成功
        {
            QMessageBox::information(this,"congratulation","regist successful");
            nextBlockSize=0;
        }
        else if(type=='Q')
        {
            QMessageBox::information(this,"sorry","regist fail");
            nextBlockSize=0;
        }
    }
    else//连接上了后
    {
        quint8 type;
        in>>type;
        nextBlockSize=0;
        if(type=='O')//请求在线用户的应答包
        {
            theShare::friendlist.clear();
            in>>theShare::friendlist;
            if(theShare::friendlist.count()>0)
            {
                for(int i=0;i<theShare::friendlist.count();i++)
                {
                    qDebug()<<theShare::friendlist.at(i);
                }
            }
            askForMy();
        }
        else if(type=='M')//返回用户精灵的包
        {
            theShare::userPoke.clear();
            quint8 num;
            in>>num;
           // qDebug()<<"have "+QString::number(num);
            //名字 等级 经验 / 类型 攻击 生命 防御 敏捷 去空格
            for(int i=0;i<num;i++)
            {
                QString _name,_style,_power,_hp,_defense,_agile;
                int _level,_exp;
                in>>_name>>_level>>_exp>>_style>>_power>>_hp>>_defense>>_agile;
                _style.remove(' ');
                _hp.remove(' ');
                _power.remove(' ');
                _defense.remove(' ');
                _agile.remove(' ');
                Poke_quality style=theShare::StringtoPokeQuality[_style];
                Quality power=theShare::StringtoQuality[_power];
                Quality hp=theShare::StringtoQuality[_hp];
                Quality defense=theShare::StringtoQuality[_defense];
                Quality agile=theShare::StringtoQuality[_agile];
                pokemon* apoke=theShare::initialPokemon(_name,_level,_exp,style,power,hp,defense,agile);
                //apoke->show();
                theShare::userPoke.append(apoke);
            }
            askForOther();
        }
        else if(type=='F')//用户姓名去空格 数目
        {
            quint8 num;
            in>>num;
            int count=theShare::OtherPoke.count();
            QString user;
            in>>user;
            user.remove(' ');
            theShare::nameToIndex.insert(user,count);
            int thenext=theShare::friendlist.indexOf(user)+1;//下一个要查找的人
            QList<pokemon*> alist;
            for(int i=0;i<num;i++)
            {
                QString _name,_style,_power,_hp,_defense,_agile;
                int _level,_exp;
                in>>_name>>_level>>_exp>>_style>>_power>>_hp>>_defense>>_agile;
                _style.remove(' ');
                _hp.remove(' ');
                _power.remove(' ');
                _defense.remove(' ');
                _agile.remove(' ');
                Poke_quality style=theShare::StringtoPokeQuality[_style];
                Quality power=theShare::StringtoQuality[_power];
                Quality hp=theShare::StringtoQuality[_hp];
                Quality defense=theShare::StringtoQuality[_defense];
                Quality agile=theShare::StringtoQuality[_agile];
                pokemon* apoke=theShare::initialPokemon(_name,_level,_exp,style,power,hp,defense,agile);
                //apoke->show();
                alist.append(apoke);
            }
            theShare::OtherPoke.append(alist);
            qDebug()<<user<<"receive ok";
            if(thenext==theShare::friendlist.count())
            {
                qDebug()<<"all get!";
                askForMyInfo();
            }
            else
            {
                emit to_ask_next(thenext);
            }
        }
        else if(type=='A')//再次请求在线好友的应答包
        {
            theShare::friendlist.clear();
            in>>theShare::friendlist;
            if(theShare::friendlist.count()>0)
            {
                for(int i=0;i<theShare::friendlist.count();i++)
                {
                    qDebug()<<theShare::friendlist.at(i);
                }
            }
            //把原来的删了
            theShare::OtherPoke.clear();
            theShare::nameToIndex.clear();
            askForOtherAgain();

        }
        else if(type=='B')//再次请求好友精灵的应答包
        {
            quint8 num;
            in>>num;
            int count=theShare::OtherPoke.count();
            QString user;
            in>>user;
            user.remove(' ');
            theShare::nameToIndex.insert(user,count);
            int thenext=theShare::friendlist.indexOf(user)+1;//下一个要查找的人
            QList<pokemon*> alist;
            for(int i=0;i<num;i++)
            {
                QString _name,_style,_power,_hp,_defense,_agile;
                int _level,_exp;
                in>>_name>>_level>>_exp>>_style>>_power>>_hp>>_defense>>_agile;
                _style.remove(' ');
                _hp.remove(' ');
                _power.remove(' ');
                _defense.remove(' ');
                _agile.remove(' ');
                Poke_quality style=theShare::StringtoPokeQuality[_style];
                Quality power=theShare::StringtoQuality[_power];
                Quality hp=theShare::StringtoQuality[_hp];
                Quality defense=theShare::StringtoQuality[_defense];
                Quality agile=theShare::StringtoQuality[_agile];
               pokemon* apoke=theShare::initialPokemon(_name,_level,_exp,style,power,hp,defense,agile);
                //apoke->show();
                alist.append(apoke);
            }
            theShare::OtherPoke.append(alist);
            qDebug()<<user<<"receive ok";
            if(thenext==theShare::friendlist.count())
            {
                askForAllUser();
                qDebug()<<"all get!";
            }
            else
            {
               // emit to_ask_next(thenext);
                askForOtherPokeAgain(thenext);
            }
        }
        else if(type=='K')//我的信息应答包
        {
            QString name,numbadge,highbadge;
            int win,win1,lose,lose1,state;
            in>>name>>win>>lose>>win1>>lose1>>state>>numbadge>>highbadge;
            name.remove(' ');
            numbadge.remove(' ');
            highbadge.remove(' ');
            theShare::myInfo=player(name,win,lose,win1,lose1,state,numbadge,highbadge);
            //qDebug()<<theShare::myInfo.highbadge;
            askForAllUser();

        }
        else if(type=='U')
        {
            qDebug()<<"nihao";
            int num;
            in>>num;
            theShare::allUser.clear();
            for(int i=0;i<num;i++)
            {
                QString name,numbadge,highbadge;
                int win,win1,lose,lose1,state;
                in>>name>>win>>lose>>win1>>lose1>>state>>numbadge>>highbadge;
                name.remove(' ');
                numbadge.remove(' ');
                highbadge.remove(' ');
                player aplayer(name,win,lose,win1,lose1,state,numbadge,highbadge);
                theShare::allUser.append(aplayer);
            }
            //qDebug
            for(int i=0;i<num;i++)
            {
                QString _name=theShare::allUser.at(i).name;
                qDebug()<<_name;
            }
            //goForGame();
            //askForMyInfo();
        }
    }
}

void Widget::sendRequest()
{
    QString id=ui->id_edit->text();
    QString pw=ui->pw_edit->text();
    theShare::username=id;
    //QMessageBox::information(this,tr("error"),tr("server ip address error!"));
    QString msg=id+pw;
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('L')<<id+' '<<pw+' ';
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    theShare::socket->write(block);
    ui->state_label->setText("发送账号密码中");
}
void Widget::is_Connect()
{

}
void Widget::closeConnection()
{
   // socket.close();
    ui->login->setEnabled(false);
    ui->regist->setEnabled(false);
    Timer->start();
    ui->label->setStyleSheet("border-image: url(:/images/networkbad.png);");
    qDebug()<<"gg";

    theShare::socket->deleteLater();
}
void Widget::haveError()
{
    ui->state_label->setText(theShare::socket->errorString());
    ui->login->setEnabled(true);
    theShare::socket->deleteLater();
}



void Widget::askForOtherPoke(int i)//请求第i个好友的精灵信息
{
    QString afriend=theShare::friendlist.at(i);
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('F')<<afriend+" ";
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    theShare::socket->write(block);
    ui->state_label->setText("请求"+afriend+"的精灵information");
}

void Widget::askForOnline()
{
    theShare::nameToIndex.clear();
    theShare::friendlist.clear();
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('O');
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    theShare::socket->write(block);
   // state_label->setText("请求在线人数");
}
void Widget::askOnlineagain()//再一次查找在线人，并把对应精灵更新
{
    /*
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('A');
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    theShare::socket->write(block);
    */
    askForOnline();
}

void Widget::returnMyInformation()//
{
   /* QString name,numbadge,highbadge;
    int win,win1,lose,lose1,state;
    in>>name>>win>>lose>>win1>>lose1>>state>>numbadge>>highbadge;
    name.remove(' ');
    numbadge.remove(' ');
    highbadge.remove(' ');
    theShare::myInfo=player(name,win,lose,win1,lose1,state,numbadge,highbadge);*/

    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('T');
    QString name,numbadge,highbadge;
    int win,win1,lose,lose1,state;
    name=theShare::myInfo.name;
    numbadge=theShare::myInfo.numbadge;
    highbadge=theShare::myInfo.highbadge;
    state=1;
    win=theShare::myInfo.win;
    win1=theShare::myInfo.win1;
    lose=theShare::myInfo.lose;
    lose1=theShare::myInfo.lose1;
    out<<name<<win<<lose<<win1<<lose1<<state<<numbadge+' '<<highbadge+' ';
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    theShare::socket->write(block);
}

void Widget::returnMyPoke()
{
    QList<pokemon*> pokelist=theShare::userPoke;
    qDebug()<<pokelist.count();
    int num=theShare::userPoke.count();
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('J')<<theShare::username<<num;//写入用户姓名+数目
    for(int i=0;i<pokelist.count();i++)
    {
        pokemon* apoke=pokelist.at(i);
        QString name=apoke->get_name();
        Poke_quality _style=apoke->get_style();
        QString style=theShare::PokeQualityToString[_style];
        Quality _power,_hp,_defense,_agile;
        QString power,hp,defense,agile;
        _power=apoke->get_powerAttribute();
        _hp=apoke->get_hpAttribute();
        _defense=apoke->get_defenseAttribute();
        _agile=apoke->get_agileAttribute();
        power=theShare::QualityToString[_power];
        hp=theShare::QualityToString[_hp];
        defense=theShare::QualityToString[_defense];
        agile=theShare::QualityToString[_agile];
        int level=apoke->get_level();
        int exp=apoke->get_exp();
        //QString
        out<<name<<level<<exp<<style+" "<<power+" "<<hp+" "<<defense+" "
          <<agile+" ";//名字 等级 经验 / 类型 攻击 生命 防御 敏捷 去空格
    }
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    theShare::socket->write(block);
    qDebug()<<"send!";
}

void Widget::askForAllUser()//ask for all user
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('U')<<theShare::username;
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    theShare::socket->write(block);
}
void Widget::askForOther()
{
    theShare::OtherPoke.clear();
    theShare::nameToIndex.clear();
    if(theShare::friendlist.count()>0)
    {

         askForOtherPoke(0);
    }
    else
        askForMyInfo();
}
void Widget::askForOtherAgain()
{
    if(theShare::friendlist.count()>0)
    {
        askForOtherPokeAgain(0);
    }
}

void Widget::askForOtherPokeAgain(int i)
{
    QString afriend=theShare::friendlist.at(i);
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('B')<<afriend+" ";
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    theShare::socket->write(block);
}

void Widget::askForMyInfo()//
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('K')<<theShare::username;
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    theShare::socket->write(block);
    ui->state_label->setText("请求我的信息");
}

void Widget::askForMy()
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('M');
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    theShare::socket->write(block);
    ui->state_label->setText("请求我的精灵信息");
}

void Widget::goForGame()
{

    //请求我的信息 以及所有在线用户
    //this->hide();
    this->hide();
    BlurPicker* Pick=new BlurPicker();
    Pick->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Application Picker"));

    //blurPicker.setFixedSize(1920, 400);
    Pick->resize(960,540);
    Pick->show();
}

void Widget::registNew(QString name, QString pw)
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('R');
    out<<name+" "<<pw;
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    theShare::socket->write(block);
    ui->state_label->setText("regist");
}

void Widget::networkGreat()
{
    Timer->stop();
    ui->login->setEnabled(true);
    ui->regist->setEnabled(true);
    ui->label->setStyleSheet("border-image: url(:/images/ball2.png);");
}

void Widget::on_regist_clicked()
{
    //
    this->hide();
    Regist* registDialog=new Regist;
    registDialog->show();
    connect(registDialog,SIGNAL(destroyed(QObject*)),this,SLOT(show()));
    connect(registDialog,SIGNAL(registNew(QString,QString)),this,SLOT(registNew(QString,QString)));

}


