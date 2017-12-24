#include "lapras.h"

#include"type.h"


Lapras::Lapras(pokemon *parent):pokemon(parent)
{
    this->set_name("Lapras");
    the_type=water;
}

Lapras::Lapras(Poke_quality a_quality):pokemon(a_quality)
{
    this->set_name("Lapras");
    the_type=water;
}

Lapras::Lapras(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name)
    :pokemon(name,level,exp,_style,_power,_hp,_defense,_agile)
{
    the_type=water;
}

void Lapras::toAttack(QString &SkillName, int &hurt)
{
    int n=qrand()%3;
    switch(n)
    {
    case 0:
        SkillName="HydroPump";
        hurt=this->get_power()*3;
        break;
    case 1:
        SkillName="IceBeam";
        hurt=this->get_power()*2;
        break;
    case 2:
        SkillName="WaterPulse";
        hurt=this->get_power()*2;
        break;
    case 3:
        SkillName="IceShard";
        hurt=this->get_power()*1;
        break;
    }
}




Poke_type Lapras::get_type() const
{
    return the_type;
}
