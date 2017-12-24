#include "snorlax.h"

#include"type.h"


Snorlax::Snorlax(pokemon *parent):pokemon(parent)
{
    this->set_name("Snorlax");
    the_type=general;
}

Snorlax::Snorlax(Poke_quality a_quality):pokemon(a_quality)
{
    this->set_name("Snorlax");
    the_type=general;
}

Snorlax::Snorlax(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name)
    :pokemon(name,level,exp,_style,_power,_hp,_defense,_agile)
{
    the_type=general;
}

void Snorlax::toAttack(QString &SkillName, int &hurt)
{
    int n=qrand()%3;
    switch(n)
    {
    case 0:
        SkillName="GigaImpact";
        hurt=this->get_power()*3;
        break;
    case 1:
        SkillName="BodySlam";
        hurt=this->get_power()*2;
        break;
    case 2:
        SkillName="ChipAway";
        hurt=this->get_power()*2;
        break;
    case 3:
        SkillName="Tackle";
        hurt=this->get_power()*1;
        break;
    }
}




Poke_type Snorlax::get_type() const
{
    return the_type;
}
