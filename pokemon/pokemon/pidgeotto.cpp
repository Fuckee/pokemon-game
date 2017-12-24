#include "pidgeotto.h"

#include"type.h"


Pidgeotto::Pidgeotto(pokemon *parent):pokemon(parent)
{
    this->set_name("Pidgeotto");
    the_type=fly;
}

Pidgeotto::Pidgeotto(Poke_quality a_quality):pokemon(a_quality)
{
    this->set_name("Pidgeotto");
    the_type=fly;
}

Pidgeotto::Pidgeotto(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name)
    :pokemon(name,level,exp,_style,_power,_hp,_defense,_agile)
{
    the_type=fly;
}

void Pidgeotto::toAttack(QString &SkillName, int &hurt)
{
    int n=qrand()%3;
    switch(n)
    {
    case 0:
        SkillName="Hurricane";
        hurt=this->get_power()*3;
        break;
    case 1:
        SkillName="WingAttack";
        hurt=this->get_power()*2;
        break;
    case 2:
        SkillName="Twister";
        hurt=this->get_power()*2;
        break;
    case 3:
        SkillName="QuickAttack";
        hurt=this->get_power()*1;
        break;
    }
}




Poke_type Pidgeotto::get_type() const
{
    return the_type;
}
