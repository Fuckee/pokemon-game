#ifndef THESHARE_H
#define THESHARE_H

#include"pokemon/all_head.h"
#include"widget.h"
#include<QTcpSocket>
#include"player.h"
//全局变量
class theShare
{
public:
   // theShare();
    static QList<QString> friendlist;//在线好友
    static QMap<QString,Poke_quality> StringtoPokeQuality;//将字符串映射为对应精灵类型
    static QMap<QString,Quality> StringtoQuality;//将字符串映射为对应精灵属性
    static QMap<Poke_quality,QString> PokeQualityToString;//将类型映射为字符串
    static QMap<Quality,QString> QualityToString;//将属性映射为字符串
    static QMap<QString,int> nameToIndex;//在线用户的精灵包与otherpoke中下标的转换
    static QList<pokemon*> userPoke;//玩家的精灵列表
    static QList< QList<pokemon*> > OtherPoke;//其他注册用户的精灵
    static QTcpSocket*  socket;//用于与服务器进行数据传输的socket
    static pokemon* initialPokemon(QString _name,int _level,int _exp,Poke_quality style,Quality power,
                                   Quality hp,Quality defense,Quality agile);//初始化精灵的函数
    static QString username;//用户姓名
    static player myInfo;//用户信息
    static QList<player> allUser;//全部注册用户
    static player findPlayer(QString name);//根据玩家名字返回玩家
    static pokemon* randPoke(int hard);//随机生成小精灵

};

#endif // THESHARE_H
