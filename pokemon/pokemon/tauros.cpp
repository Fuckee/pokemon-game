#include "tauros.h"

#include"type.h"


Tauros::Tauros(pokemon *parent):pokemon(parent)
{
    this->set_name("Tauros");
    the_type=general;
}

Tauros::Tauros(Poke_quality a_quality):pokemon(a_quality)
{
    this->set_name("Tauros");
    the_type=general;
}

Tauros::Tauros(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name)
    :pokemon(name,level,exp,_style,_power,_hp,_defense,_agile)
{
    the_type=general;
}

void Tauros::toAttack(QString &SkillName, int &hurt)
{
    int n=qrand()%3;
    switch(n)
    {
    case 0:
        SkillName="GigaImpact";
        hurt=this->get_power()*3;
        break;
    case 1:
        SkillName="ZenHeadbutt";
        hurt=this->get_power()*2;
        break;
    case 2:
        SkillName="PayBack";
        hurt=this->get_power()*2;
        break;
    case 3:
        SkillName="Pursuit";
        hurt=this->get_power()*1;
        break;
    }
}




Poke_type Tauros::get_type() const
{
    return the_type;
}
