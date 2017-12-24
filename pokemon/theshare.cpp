#include "theshare.h"
#include<QTcpSocket>
QList<QString> theShare::friendlist;

QMap<QString,Poke_quality> theShare::StringtoPokeQuality;//字符串与精灵类型
QMap<QString,Quality> theShare::StringtoQuality;//字符串与精灵属性
QMap<Poke_quality,QString> theShare::PokeQualityToString;
QMap<Quality,QString> theShare::QualityToString;
QMap<QString,int> theShare::nameToIndex;//在线用户的精灵包与otherpoke中下标的转换
QList<pokemon*> theShare::userPoke;//用户精灵
QList< QList<pokemon*> > theShare::OtherPoke;//其他用户的精灵
QTcpSocket*  theShare::socket;//用于连接的socket
QString theShare::username;//用户姓名

player theShare::myInfo;//用户信息
QList<player> theShare::allUser;//所有用户信息

pokemon *theShare::initialPokemon(QString name, int level, int exp, Poke_quality style, Quality power, Quality hp, Quality defense,Quality agile)
{
    pokemon* compoke;
    if(name=="Bulbasaur")
    {
        compoke=new Bulbasaur(level,exp,style,power,hp,defense,agile);
        return compoke;
    }
    else if(name=="Charmander")
    {
        compoke=new Charmander(level,exp,style,power,hp,defense,agile);
        return compoke;
    }
    else if(name=="Kingler")
    {
        compoke=new Kingler(level,exp,style,power,hp,defense,agile);
        return compoke;
    }
    else if(name=="Lapras")
    {
        compoke=new Lapras(level,exp,style,power,hp,defense,agile);
        return compoke;
    }
    else if(name=="Muk")
    {
        compoke=new Muk(level,exp,style,power,hp,defense,agile);
        return compoke;
    }
    else if(name=="Pidgeotto")
    {
        compoke=new Pidgeotto(level,exp,style,power,hp,defense,agile);
        return compoke;
    }
    else if(name=="Pikachu")
    {
        compoke=new Pikachu(level,exp,style,power,hp,defense,agile);
        return compoke;
    }
    else if(name=="Primeape")
    {
        compoke=new Primeape(level,exp,style,power,hp,defense,agile);
        return compoke;
    }
    else if(name=="Snorlax")
    {
        compoke=new Snorlax(level,exp,style,power,hp,defense,agile);
        return compoke;
    }
    else if(name=="Squirtle")
    {
        compoke=new Squirtle(level,exp,style,power,hp,defense,agile);
        return compoke;
    }
    else if(name=="Tauros")
    {
        compoke=new Tauros(level,exp,style,power,hp,defense,agile);
        return compoke;
    }
}

player theShare::findPlayer(QString name)
{
    for(int i=0;i<allUser.count();i++)
    {
        if(allUser.at(i).name==name)
            return allUser.at(i);
    }
    qDebug()<<"no find the man!";
}

pokemon *theShare::randPoke(int hard)//0:0-3 1:4-7 2:8-11 3:12-15
{
    //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int level,exp=0;
    Poke_quality style;
    Quality power,hp,defense,agile;
    int n;
    n=qrand()%4;
    if(n==0)
    {
        style=strong;
        power=excellent;
        hp=great;
        defense=great;
        agile=normal;
    }
    else if(n==1)
    {
        style=fast;
        power=normal;
        hp=great;
        defense=great;
        agile=excellent;
    }
    else if(n==2)
    {
        style=defendful;
        power=great;
        hp=great;
        defense=excellent;
        agile=normal;
    }
    else if(n==3)
    {
        style=hpful;
        power=normal;
        hp=excellent;
        defense=great;
        agile=bad;
    }
   level=qrand()%4;
   level+=4*hard;
    n=qrand()%11;
    QString name;
    pokemon* apoke;
    if(n==0)
    {
        name="Bulbasaur";
        return apoke=new Bulbasaur(level,exp,style,power,hp,defense,agile);
    }
    else if(n==1)
    {
        name="Tauros";return apoke=new Tauros(level,exp,style,power,hp,defense,agile);
    }
    else if(n==2)
    {
        name="Squirtle";return apoke=new Squirtle(level,exp,style,power,hp,defense,agile);
    }
    else if(n==3)
    {
        name="Snorlax";return apoke=new Snorlax(level,exp,style,power,hp,defense,agile);
    }
    else if(n==4)
    {
        name="Primeape";return apoke=new Primeape(level,exp,style,power,hp,defense,agile);
    }
    else if(n==5)
    {
        name="Pikachu";return apoke=new Pikachu(level,exp,style,power,hp,defense,agile);
    }
    else if(n==6)
    {
        name="Pidgeotto";return apoke=new Pidgeotto(level,exp,style,power,hp,defense,agile);
    }
    else if(n==7)
    {
        name="Muk";return apoke=new Muk(level,exp,style,power,hp,defense,agile);
    }
    else if(n==8)
    {
        name="Lapras";return apoke=new Lapras(level,exp,style,power,hp,defense,agile);
    }
    else if(n==9)
    {
        name="Kingler";return apoke=new Kingler(level,exp,style,power,hp,defense,agile);
    }
    else if(n==10)
    {
        name="Charmander";return apoke=new Charmander(level,exp,style,power,hp,defense,agile);
    }



}
