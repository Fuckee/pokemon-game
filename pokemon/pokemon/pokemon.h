#ifndef POKEMON_H
#define POKEMON_H

#include <QObject>
#include"type.h"
#include"all_head.h"
#include<QString>
class pokemon
{

public:
    pokemon(Poke_quality a_quality);
    pokemon(QString name,int level,int exp,Poke_quality _style,Quality _power,Quality _hp,Quality _defense,Quality _agile);
    pokemon(QString name,int level,Poke_quality _style,Quality _power,Quality _hp,Quality _defense,Quality _agile);
    pokemon(pokemon *theone);


private:
    enum { exp_base=10}; //一个经验格
    Poke_quality the_style;//类型 力量型 肉盾型 防御型 敏捷型
    Quality power_attribute;//攻击力资质 攻击力=攻击属性*level*2
    Quality hp_attribute;//生命值资质    生命值=生命属性*level*4
    Quality defense_attribute;//防御资质 防御力=防御属性*level*1
    Quality agile_attribute;//敏捷资质  先天决定不随等级变化  1 2 3 4
    QString the_name;//名字
    int level;//当前等级
    int  exp;//当前经验值
    int power;//当前攻击力
    int defense;//当前防御力
    int hp;//当前生命值上限
    int attack_interval;//攻击间隔 比如5s攻击一下
    int cur_hp;
public:
    virtual void toAttack(QString& SkillName,int& hurt)=0;
    virtual ~pokemon(){}
    void show()const;
    QString get_name()const;
    int get_power()const;
    int get_level()const;
    int get_exp()const;
    int get_defense()const;
    int get_hp()const;
    int get_attack_interval()const;
    Poke_quality get_style()const;
    Quality get_powerAttribute()const;
    Quality get_hpAttribute()const;
    Quality get_defenseAttribute()const;
    Quality get_agileAttribute()const;
    int get_cur_hp()const;


    void set_name(QString new_name);
    void set_level(int add_level);
    void add_exp(int add_exp);
    void set_attribute();//根据当前等级设置各项属性 除了敏捷属性
   // virtual void toAttack(QString& SkillName,int& hurt)=0;
};
#endif // POKEMON_H
