#include "bulbasaur.h"
#include"type.h"


Bulbasaur::Bulbasaur(pokemon *parent):pokemon(parent)
{
    this->set_name("Bulbasaur");
    the_type=glass;
}

Bulbasaur::Bulbasaur(Poke_quality a_quality):pokemon(a_quality)
{
    this->set_name("Bulbasaur");
    the_type=glass;
}

Bulbasaur::Bulbasaur(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name)
    :pokemon(name,level,exp,_style,_power,_hp,_defense,_agile)
{
    the_type=glass;
}

void Bulbasaur::toAttack(QString &SkillName, int &hurt)
{
    int n=qrand()%3;
    switch(n)
    {
    case 0:
        SkillName="SeedBomb";
        hurt=this->get_power()*3;
        break;
    case 1:
        SkillName="TakeDown";
        hurt=this->get_power()*2;
        break;
    case 2:
        SkillName="RazorLeaf";
        hurt=this->get_power()*2;
        break;
    case 3:
        SkillName="VineWhip";
        hurt=this->get_power()*1;
        break;
    }
}




Poke_type Bulbasaur::get_type() const
{
    return the_type;
}

