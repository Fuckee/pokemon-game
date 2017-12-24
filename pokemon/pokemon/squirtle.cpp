#include "squirtle.h"

Squirtle::Squirtle(pokemon *parent):pokemon(parent)
{
    this->set_name("Squirtle");
    the_type=water;
}

Squirtle::Squirtle(Poke_quality a_quality):pokemon(a_quality)
{
    this->set_name("Squirtle");
    the_type=water;
}

Squirtle::Squirtle(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name)
    :pokemon(name,level,exp,_style,_power,_hp,_defense,_agile)
{
    the_type=water;
}

void Squirtle::toAttack(QString &SkillName, int &hurt)
{
    int n=qrand()%3;
    switch(n)
    {
    case 0:
        SkillName="Hydro Pump";
        hurt=this->get_power()*3;
        break;
    case 1:
        SkillName="Aqua Tail";
        hurt=this->get_power()*2;
        break;
    case 2:
        SkillName="Skull Bash";
        hurt=this->get_power()*2;
        break;
    case 3:
        SkillName="Bubble";
        hurt=this->get_power()*1;
        break;
    }
}



Poke_type Squirtle::get_type() const
{
    return the_type;
}
