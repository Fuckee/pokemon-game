#include"all_head.h"
using namespace std;
Quality get_rand()
{
    int n = qrand()%4;
    if(n==0)
        return excellent;
    else if(n==1)
        return great;
    else if(n==2)
        return normal;
    else
        return bad;
}

pokemon::pokemon( Poke_quality a_quality)
{
    the_style=a_quality;
    switch (the_style)//设置各项属性
    {
    case hpful:
        power_attribute=get_rand();
        hp_attribute=excellent;
        defense_attribute=get_rand();
        agile_attribute=get_rand();
        break;
    case defendful:
        power_attribute=get_rand();
        hp_attribute=get_rand();
        defense_attribute=excellent;
        agile_attribute=get_rand();
        break;
    case strong:
        power_attribute=excellent;
        hp_attribute=get_rand();
        defense_attribute=get_rand();
        agile_attribute=get_rand();
        break;
    case fast:
        power_attribute=get_rand();
        hp_attribute=get_rand();
        defense_attribute=get_rand();
        agile_attribute=excellent;
        break;
    }
    level=0;
    exp=0;
    switch (agile_attribute)
    {
        case excellent:
            attack_interval=1;
        break;
        case great:
            attack_interval=2;
        break;
        case normal:
            attack_interval=3;
        break;
        case bad:
            attack_interval=4;
        break;
    }
    set_attribute();

}

pokemon::pokemon( QString name,int _level, int _exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile)
{
    the_name=name;
    level=_level;
    exp=_exp;
    the_style=_style;
    power_attribute=_power;
    hp_attribute=_hp;
    defense_attribute=_defense;
    agile_attribute=_agile;
    switch (agile_attribute)
    {
        case excellent:
            attack_interval=1;
        break;
        case great:
            attack_interval=2;
        break;
        case normal:
            attack_interval=3;
        break;
        case bad:
            attack_interval=4;
        break;
    }
    set_attribute();

}

pokemon::pokemon(pokemon *theone)
{
    the_name=theone->get_name();
    level=theone->get_level();
    exp=theone->get_exp();
    the_style=theone->get_style();
    power_attribute=theone->get_powerAttribute();
    hp_attribute=theone->get_hpAttribute();
    defense_attribute=theone->get_defenseAttribute();
    agile_attribute=theone->get_agileAttribute();
    switch (agile_attribute)
    {
        case excellent:
            attack_interval=1;
        break;
        case great:
            attack_interval=2;
        break;
        case normal:
            attack_interval=3;
        break;
        case bad:
            attack_interval=4;
        break;
    }
    set_attribute();

}



void pokemon::toAttack1()
{

}

void pokemon::toAttack2()
{
    qDebug()<<"go attack!";
}


int pokemon::get_power() const
{
    return this->power;
}

QString pokemon::get_name() const
{
    return this->the_name;
}

int pokemon::get_level() const
{
    return this->level;
}

int pokemon::get_exp() const
{
    return this->exp;
}

int pokemon::get_defense() const
{
    return this->defense;
}

int pokemon::get_hp() const
{
    return this->hp;
}

int pokemon::get_attack_interval() const
{
    return this->attack_interval;
}

int pokemon::get_cur_hp() const
{
    return cur_hp;
}

Quality pokemon::get_powerAttribute()const
{
    return power_attribute;
}

Quality pokemon::get_hpAttribute()const
{
    return hp_attribute;
}

Quality pokemon::get_defenseAttribute()const
{
    return defense_attribute;
}

Quality pokemon::get_agileAttribute()const
{
    return agile_attribute;
}
Poke_quality pokemon::get_style()const
{
    return the_style;
}

void pokemon::set_name(QString new_name)
{
    this->the_name=new_name;
}

void pokemon::set_level(int add_level)
{
    if(level<15){
        level+=add_level;
        set_attribute();
    }
    else{
       return;
    }
}

void pokemon::add_exp(int add_exp)
{
      this->exp+=add_exp;
     //judge whether level up
    while(exp>=(level+1)*exp_base){
        set_level(1);
        //change attribut

        //
        exp-=level*exp_base;
    }
}
#define grow_hp 3
#define grow_power  2
#define grow_defense  1
void pokemon::set_attribute()
{
    int j=level+1;
    power=j*grow_power*power_attribute;
    hp=j*grow_hp*hp_attribute;
    defense=j*grow_defense*defense_attribute;
    cur_hp=hp;
}
void pokemon::show()const
{
    qDebug()<<"name:";
    qDebug()<<get_name();
    qDebug()<<"power:";
    qDebug()<<get_power();
    qDebug()<<"defense:";
    qDebug()<<get_defense();
    qDebug()<<"hp_max:";
    qDebug()<<get_hp();
    qDebug()<<"attack interval:";
    qDebug()<<get_attack_interval();
    qDebug()<<"current state";
    qDebug()<<"current hp:";
    qDebug()<<get_cur_hp()<<"  ";
    qDebug()<<"current level:";
    qDebug()<<get_level()<<"  ";
    qDebug()<<"current exp:";
    qDebug()<<get_exp();
}
