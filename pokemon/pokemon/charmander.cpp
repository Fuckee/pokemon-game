#include "charmander.h"

Charmander::Charmander(pokemon *parent):pokemon(parent)
{
    this->set_name("Charmander");
    the_type=fire;
}

Charmander::Charmander(Poke_quality a_quality):pokemon(a_quality)
{
    this->set_name("Charmander");
    the_type=fire;
}

Charmander::Charmander( int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name)
    :pokemon(name,level,exp,_style,_power,_hp,_defense,_agile)
{
    the_type=fire;
}

void Charmander::toAttack(QString &SkillName, int &hurt)
{
    int n=qrand()%3;
    switch(n)
    {
    case 0:
        SkillName="DragonRage";
        hurt=this->get_power()*3;
        break;
    case 1:
        SkillName="Flamethrower";
        hurt=this->get_power()*2;
        break;
    case 2:
        SkillName="FireSpin";
        hurt=this->get_power()*2;
        break;
    case 3:
        SkillName="Ember";
        hurt=this->get_power()*1;
        break;
    }
}





Poke_type Charmander::get_type() const
{
    return the_type;
}
