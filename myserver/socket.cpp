#include "socket.h"
#include<QDataStream>
#include"pokemon/bulbasaur.h"
Socket::Socket(QObject *parent,int number):QTcpSocket(parent)
{
    state=false;
    nextBlockSize=0;
    connect(this,SIGNAL(readyRead()),this,SLOT(toRead()));
    connect(this,SIGNAL(disconnected()),this,SLOT(stop()));
    _id="";
    _number=number;
    QString connectionName="connection"+QString::number(_number);
    qDebug()<<connectionName;
    mydb=QSqlDatabase::addDatabase("QSQLITE",connectionName);

    mydb.setDatabaseName("E:\sqlite\mydata.db");
    query=QSqlQuery(mydb);
    mydb.open();
    StringtoPokeQuality.insert("hpful",hpful);
    StringtoPokeQuality.insert("strong",strong);
    StringtoPokeQuality.insert("defendful",defendful);
    StringtoPokeQuality.insert("fast",fast);
    StringtoQuality.insert("excellent",excellent);
    StringtoQuality.insert("great",great);
    StringtoQuality.insert("normal",normal);
    StringtoQuality.insert("bad",bad);

    PokeQualityToString.insert(hpful,"hpful");
    PokeQualityToString.insert(strong,"strong");
    PokeQualityToString.insert(defendful,"defendful");
    PokeQualityToString.insert(fast,"fast");
    QualityToString.insert(excellent,"excellent");
    QualityToString.insert(great,"great");
    QualityToString.insert(normal,"normal");
    QualityToString.insert(bad,"bad");


}

void Socket::sendMessage(quint8 type, QString msg)//发送连接应答的包
{
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<type;
    switch (type)
    {
        case 'Y':
            break;
         case 'N':
            break;



    }
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    this->write(block);
}



void Socket::toRead()//有数据到达即触发
{
    QDataStream in(this);
    in.setVersion(QDataStream::Qt_5_7);
    //判断包的大小是否已知
    if(nextBlockSize==0)
    {
        if(bytesAvailable()<sizeof(quint16))
        {
            return;//数据包还太小，等待继续接受
        }
        in>>nextBlockSize;//读取下个数据包的长度
    }
    if(bytesAvailable()<nextBlockSize)
    {
        return;//太小了，等下继续接受
    }
    //可以开始读取数据包了
    qDebug()<<nextBlockSize;
    quint8 type;//数据包类型
    in>>type;
    //qDebug()<<type;
    if(type=='L')
    {
        //登陆数据包
        //进入数据库查找
        QString id,pw;
        in>>id>>pw;

        if(check_login(id,pw))//正确
        {
            id.remove(' ');//移除用于分割的空格
            emit connect_success(id,pw,this);//发出连接成功的信号
            state=true;
            //发送成功连接回馈
            sendMessage('Y');
            _id=id;
            nextBlockSize=0;
        }
        else
        {
            //发送错误信息回馈
            sendMessage('N');
            nextBlockSize=0;
            this->deleteLater();
        }
    }
    else if(type=='R')
    {
        nextBlockSize=0;
        QString name,pw;
        in>>name>>pw;
        name.remove(' ');
        pw.remove(' ');
        registNew(name,pw);
    }
    else if(type=='O')
    {

        //请求在线用户的数据包
        returnOnline();//进入数据库查询返回信息
       // qDebug()<<"ask my pokemon";
        nextBlockSize=0;
    }
    else if(type=='M')
    {
        //请求用户的精灵的数据包
        qDebug()<<"ask my pokemon";
        nextBlockSize=0;
        returnUserPoke();
    }
    else if(type=='F')
    {
        nextBlockSize=0;
        QString name;
        in>>name;
        name.remove(' ');
        qDebug()<<"askfor"+name;
        returnSomeBody(name);
    }
    else if(type=='A')
    {
        nextBlockSize=0;
        returnOnlineagain();
    }
    else if(type=='B')
    {
        nextBlockSize=0;
        QString name;
        in>>name;
        name.remove(' ');
        qDebug()<<"askfor"+name;
        returnSomeBodyAgain(name);
    }
    else if(type=='J')//更新用户精灵的包
    {
        nextBlockSize=0;
        QString username;
        QList<pokemon*> alist;
        in>>username;
        username.remove(' ');
        int num;
        in>>num;
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
            Poke_quality style=StringtoPokeQuality[_style];
            Quality power=StringtoQuality[_power];
            Quality hp=StringtoQuality[_hp];
            Quality defense=StringtoQuality[_defense];
            Quality agile=StringtoQuality[_agile];
           pokemon* apoke=new pokemon(_name,_level,_exp,style,power,hp,defense,agile);
            //apoke->show();
            alist.append(apoke);
        }
        updateUser(username,alist);
    }
    else if(type=='K')//返回用户信息
    {
        nextBlockSize=0;
        QString name;
        in>>name;
        returnInfo(name);
    }
    else if(type=='U')
    {
        QString name;
        in>>name;
        nextBlockSize=0;
        returnAllInfo(name);
    }
    else if(type=='T')
    {
        //out<<name<<win<<lose<<win1<<lose1<<state<<numbadge+' '<<highbadge+' ';
        nextBlockSize=0;
        QString name,numbadge,highbadge;
        int win,win1,lose,lose1,state;
        in>>name>>win>>lose>>win1>>lose1>>state>>numbadge>>highbadge;
        numbadge.remove(' ');
        highbadge.remove(' ');
        player aplayer(name,win,lose,win1,lose1,state,numbadge,highbadge);
        updateMy(aplayer);
    }

}

void Socket::stop()//断开连接的处理
{
    if(_id!="")
    {
        //state=0

        query.exec("update clientlist set state=0 where name='"+_id+"'");
        emit stopConnect(this->socketDescriptor(),_id);
    }

}

bool Socket::check_login(QString name1, QString password1)//检查登陆
{
    QString name=name1.remove(' ');
    QString password=password1.remove(' ');
    query.exec("SELECT password,state FROM clientlist where name='"+name+"'");
    //query.exec("select * from userlist");
    if(!query.next())
        return false;
    QString answer=query.value(0).toString();
    int state=query.value(1).toInt();
    if(state==1)
        return false;
    if(answer==password)
    {
        //把state改为1;
        query.exec("update clientlist set state=1 where name='"+name+"'");
        return true;
    }
    else
        return false;
}

void Socket::returnOnline()//返回在线用户
{
    QList<QString> list;
   // qDebug()<<"???";
    query.exec("SELECT name FROM clientlist ");
    while(query.next())
    {
        QString name=query.value(0).toString();
        if(name!=_id)
        {
            list.append(name);
        }
    }//将查询结果保存在List中
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('O');
    out<<list;
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    this->write(block);
}

void Socket::returnOnlineagain()//第二次请求在线用户的返回
{
    QList<QString> list;
    query.exec("SELECT name FROM clientlist ");
    while(query.next())
    {
        QString name=query.value(0).toString();
        if(name!=_id)
        {
            list.append(name);
        }
    }//将查询结果保存在List中
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('A');
    out<<list;
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    this->write(block);
}

void Socket::returnUserPoke()//返回用户的精灵
{
    QList< pokemon*>  pokemonlist;
    query.exec("select * from "+_id);
    int num=0;
    while(query.next())
    {
        num++;
    }
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('M')<<quint8(num);//写入精灵数目
    query.exec("select * from "+_id);
    while(query.next())
    {
        QString name=query.value(1).toString();
        //QString
        int level=query.value(2).toInt();
        int exp=query.value(3).toInt();
        QString _style=query.value(4).toString();
        QString _power=query.value(5).toString();
        QString _hp=query.value(6).toString();
        QString _defense=query.value(7).toString();
        QString _agile=query.value(8).toString();
        Poke_quality style=StringtoPokeQuality[_style];
        Quality power=StringtoQuality[_power];
        Quality hp=StringtoQuality[_hp];
        Quality defense=StringtoQuality[_defense];
        Quality agile=StringtoQuality[_agile];
        out<<name<<level<<exp<<_style+" "<<_power+" "<<_hp+" "<<_defense+" "
          <<_agile+" ";//名字 等级 经验 / 类型 攻击 生命 防御 敏捷 去空格
    }
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    this->write(block);
    qDebug()<<"send!";
}

void Socket::returnSomeBody(QString thename)//根据姓名返回对应用户的信息
{
    QList< pokemon*>  pokemonlist;
    query.exec("select * from "+thename);
    int num=0;
    while(query.next())
    {
        num++;
    }
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('F')<<quint8(num)<<thename+" ";//写入名字 +精灵数目
    query.exec("select * from "+thename);
    while(query.next())
    {
        QString name=query.value(1).toString();
        //QString
        int level=query.value(2).toInt();
        int exp=query.value(3).toInt();
        QString _style=query.value(4).toString();
        QString _power=query.value(5).toString();
        QString _hp=query.value(6).toString();
        QString _defense=query.value(7).toString();
        QString _agile=query.value(8).toString();
        Poke_quality style=StringtoPokeQuality[_style];
        Quality power=StringtoQuality[_power];
        Quality hp=StringtoQuality[_hp];
        Quality defense=StringtoQuality[_defense];
        Quality agile=StringtoQuality[_agile];
        out<<name<<level<<exp<<_style+" "<<_power+" "<<_hp+" "<<_defense+" "
          <<_agile+" ";//名字 等级 经验 / 类型 攻击 生命 防御 敏捷 去空格
    }
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    this->write(block);
    qDebug()<<"send!";
}

void Socket::returnSomeBodyAgain(QString thename)//第二次返回对应用户的信息
{
    QList< pokemon*>  pokemonlist;
    query.exec("select * from "+thename);
    int num=0;
    while(query.next())
    {
        num++;
    }
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('B')<<quint8(num)<<thename+" ";//写入名字 +精灵数目
    query.exec("select * from "+thename);
    while(query.next())
    {
        QString name=query.value(1).toString();
        //QString
        int level=query.value(2).toInt();
        int exp=query.value(3).toInt();
        QString _style=query.value(4).toString();
        QString _power=query.value(5).toString();
        QString _hp=query.value(6).toString();
        QString _defense=query.value(7).toString();
        QString _agile=query.value(8).toString();
        Poke_quality style=StringtoPokeQuality[_style];
        Quality power=StringtoQuality[_power];
        Quality hp=StringtoQuality[_hp];
        Quality defense=StringtoQuality[_defense];
        Quality agile=StringtoQuality[_agile];
        out<<name<<level<<exp<<_style+" "<<_power+" "<<_hp+" "<<_defense+" "
          <<_agile+" ";//名字 等级 经验 / 类型 攻击 生命 防御 敏捷 去空格
    }
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    this->write(block);
    qDebug()<<"send!";
}

/*void Socket::updateUser(QString username, QList<pokemon *> list)
{

    for(int i=0;i<list.count();i++)
    {
        pokemon* apoke=list.at(i);
        QString name=apoke->get_name();
        int level=apoke->get_level();
        int exp=apoke->get_exp();
        Poke_quality _style=apoke->get_style();
        Quality _power=apoke->get_powerAttribute();
        Quality _hp=apoke->get_hpAttribute();
        Quality _defense=apoke->get_defenseAttribute();
        Quality _agile=apoke->get_agileAttribute();
        QString style=PokeQualityToString[_style];
        QString power=QualityToString[_power];
        QString hp=QualityToString[_hp];
        QString defense=QualityToString[_defense];
        QString agile=QualityToString[_agile];


        query.exec("select * from "+username+" where name= '"+name+"'");
        if(!query.next())//未存在过的精灵，插入新精灵
        {
            query.exec("select * from "+username);
            int num=0;
            while(query.next())
            {
                num++;
            }
            query.prepare("insert into "+username+"(id,name,level,exp,style,power,hp,defense,agile)"
                                              "values(:id,:name,:level,:exp,:style,:power,:hp,:defense,:agile)");
            query.bindValue(":id",num+1);
            query.bindValue(":name",name);
            query.bindValue(":level",level);
            query.bindValue(":exp",exp);
            query.bindValue(":style",style);
            query.bindValue(":power",power);
            query.bindValue(":hp",hp);
            query.bindValue(":defense",defense);
            query.bindValue(":agile",agile);
        }
        else//更新
        {

            query.exec("update "+username+" set level='"+QString::number(level)+"',exp='"+QString::number(exp)+"' where name='"+name+"'");

        }

    }
}*/

void Socket::updateUser(QString username, QList<pokemon *> list)//从客户端接受数据，更新数据库
{
    query.exec("drop table "+username);
    int num=0;
    qDebug()<<list.count();
    query.exec("create table "+username+" (id int primary key,name varchar,level int,exp int,style varchar,power varchar,hp varchar,"
                                              "defense varchar,agile varchar )");
   for(int i=0;i<list.count();i++)
   {
       pokemon* apoke=list.at(i);
       QString name=apoke->get_name();
       int level=apoke->get_level();
       int exp=apoke->get_exp();
       Poke_quality _style=apoke->get_style();
       Quality _power=apoke->get_powerAttribute();
       Quality _hp=apoke->get_hpAttribute();
       Quality _defense=apoke->get_defenseAttribute();
       Quality _agile=apoke->get_agileAttribute();
       QString style=PokeQualityToString[_style];
       QString power=QualityToString[_power];
       QString hp=QualityToString[_hp];
       QString defense=QualityToString[_defense];
       QString agile=QualityToString[_agile];
       num++;
       query.prepare("insert into "+username+"(id,name,level,exp,style,power,hp,defense,agile)"
                                             "values(:id,:name,:level,:exp,:style,:power,:hp,:defense,:agile)");
       query.bindValue(":id",num);
       query.bindValue(":name",name);
       query.bindValue(":level",level);
       query.bindValue(":exp",exp);
       query.bindValue(":style",style);
       query.bindValue(":power",power);
       query.bindValue(":hp",hp);
       query.bindValue(":defense",defense);
       query.bindValue(":agile",agile);
       query.exec();
   }
}
void Socket::returnInfo(QString name)//返回对应姓名的用户信息
{
    query.exec("select * from clientlist where name='"+name+"'");
    if(query.next())
    {
        int state=query.value(2).toInt();
        int win=query.value(3).toInt();
        int lose=query.value(4).toInt();
        QString numbadge=query.value(5).toString();
        QString highbadge=query.value(6).toString();
        int win1=query.value(7).toInt();
        int lose1=query.value(8).toInt();
        QByteArray block;
        QDataStream out(&block,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_7);
        out<<quint16(0)<<quint8('K');
        out<<name<<win<<lose<<win1<<lose1<<state<<numbadge+" "<<highbadge+" ";
        out.device()->seek(0);
        out<<quint16(block.size()-sizeof(quint16));
        this->write(block);

    }//

}

void Socket::returnAllInfo(QString myname)//返回有所用户的信息
{
    int num=0;
    query.exec("select * from clientlist");
    while(query.next())
    {
        num++;
    }
    QByteArray block;
    QDataStream out(&block,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_7);
    out<<quint16(0)<<quint8('U')<<num-1;
    query.exec("select * from clientlist");
    while(query.next())
    {
        QString name=query.value(0).toString();
        if(name==myname)
            continue;
        int state=query.value(2).toInt();
        int win=query.value(3).toInt();
        int lose=query.value(4).toInt();
        QString numbadge=query.value(5).toString();
        QString highbadge=query.value(6).toString();
        int win1=query.value(7).toInt();
        int lose1=query.value(8).toInt();
        out<<name<<win<<lose<<win1<<lose1<<state<<numbadge+" "<<highbadge+" ";
    }//
    out.device()->seek(0);
    out<<quint16(block.size()-sizeof(quint16));
    this->write(block);

}

void Socket::registNew(QString name, QString pw)//注册新用户
{
    qDebug()<<"regist name:"+name;
    query.exec("select * from clientlist where name='"+name+"'");
    if(query.next())
    {
        qDebug()<<"the name has exist gg";
        QByteArray block;
        QDataStream out(&block,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_7);
        out<<quint16(0)<<quint8('Q');
        out.device()->seek(0);
        out<<quint16(block.size()-sizeof(quint16));
        this->write(block);
    }
    else
    {
        qDebug()<<"regist success!";
        query.prepare("insert into clientlist(name,password,state,win,lose,numbadge,highbadge,win1,lose1)"
                      "values(:name,:password,:state,:win,:lose,:numbadge,:highbadge,:win1,:lose1)");
        query.bindValue(":name",name);
        query.bindValue(":password",pw);
        query.bindValue(":state",0);
        query.bindValue(":win",0);
        query.bindValue(":lose",0);
        query.bindValue(":numbadge","null");
        query.bindValue(":highbadge","null");
        query.bindValue(":win1",0);
        query.bindValue(":lose1",0);
        query.exec();
        QByteArray block;
        QDataStream out(&block,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_7);
        out<<quint16(0)<<quint8('P');
        out.device()->seek(0);
        out<<quint16(block.size()-sizeof(quint16));
        this->write(block);

        //随机送3只精灵
        QStringList names;
        names<<"Charmander"<<"Bulbasaur"<<"Squirtle";
        query.exec("create table "+name+" (id int primary key,name varchar,level int,"
                                                  "exp int,style varchar,power varchar,hp varchar,"
                                                  "defense varchar,agile varchar )");
        for(int i=0;i<3;i++)
        {
            query.prepare("insert into "+name+"(id,name,level,exp,style,power,hp,defense,agile)"
                                              "values(:id,:name,:level,:exp,:style,:power,:hp,:defense,:agile)");
            QString name=names[i];
            int level=0,exp=0;
            QString style="strong";
            QString power="great";
            QString hp="normal";
            QString defense="great";
            QString agile="great";
            query.bindValue(":id",i+1);
            query.bindValue(":name",name);
            query.bindValue(":level",level);
            query.bindValue(":exp",exp);
            query.bindValue(":style",style);
            query.bindValue(":power",power);
            query.bindValue(":hp",hp);
            query.bindValue(":defense",defense);
            query.bindValue(":agile",agile);
            query.exec();
        }



    }
}

void Socket::updateMy(player aplayer)//更新用户信息
{
    //update clientlist set   .. where name=
    //name,password,state,win,lose,numbadge,highbadge,win1,lose1
    QString name=aplayer.name;
    int _win=aplayer.win,_win1=aplayer.win1,_lose=aplayer.lose,_lose1=aplayer.lose1;
    QString win=QString::number(_win);
    QString win1=QString::number(_win1);
    QString lose=QString::number(_lose);
    QString lose1=QString::number(_lose1);
    query.exec("update clientlist set win='"+win+"',win1='"+win1+"',lose='"
               +lose+"',lose1='"+lose1+"' where name='"+name+"'");
}

