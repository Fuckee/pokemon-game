#include "kingler.h"
#include"type.h"
Kingler::Kingler(pokemon *parent):pokemon(parent)
{
    this->set_name("Kingler");
    the_type=water;
}

Kingler::Kingler(Poke_quality a_quality):pokemon(a_quality)
{
    this->set_name("Kingler");
    the_type=water;
}

Kingler::Kingler(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name)
    :pokemon(name,level,exp,_style,_power,_hp,_defense,_agile)
{
    the_type=water;
}

void Kingler::toAttack(QString &SkillName, int &hurt)
{
    int n=qrand()%3;
    switch(n)
    {
    case 0:
        SkillName="Crabhammer";
        hurt=this->get_power()*3;
        break;
    case 1:
        SkillName="BubbleBeam";
        hurt=this->get_power()*2;
        break;
    case 2:
        SkillName="MetalClaw";
        hurt=this->get_power()*2;
        break;
    case 3:
        SkillName="Bubble";
        hurt=this->get_power()*1;
        break;
    }
}




Poke_type Kingler::get_type() const
{
    return the_type;
}

