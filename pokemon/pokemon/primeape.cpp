#include "primeape.h"

#include"type.h"


Primeape::Primeape(pokemon *parent):pokemon(parent)
{
    this->set_name("Primeape");
    the_type=fight;
}

Primeape::Primeape(Poke_quality a_quality):pokemon(a_quality)
{
    this->set_name("Primeape");
    the_type=fight;
}

Primeape::Primeape(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name)
    :pokemon(name,level,exp,_style,_power,_hp,_defense,_agile)
{
    the_type=fight;
}

void Primeape::toAttack(QString &SkillName, int &hurt)
{
    int n=qrand()%3;
    switch(n)
    {
    case 0:
        SkillName="SeismicToss";
        hurt=this->get_power()*3;
        break;
    case 1:
        SkillName="Outrage";
        hurt=this->get_power()*2;
        break;
    case 2:
        SkillName="KarateChop";
        hurt=this->get_power()*2;
        break;
    case 3:
        SkillName="Scratch";
        hurt=this->get_power()*1;
        break;
    }
}




Poke_type Primeape::get_type() const
{
    return the_type;
}
