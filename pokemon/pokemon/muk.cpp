#include "muk.h"

#include"type.h"


Muk::Muk(pokemon *parent):pokemon(parent)
{
    this->set_name("Muk");
    the_type=poison;
}

Muk::Muk(Poke_quality a_quality):pokemon(a_quality)
{
    this->set_name("Muk");
    the_type=poison;
}

Muk::Muk(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name)
    :pokemon(name,level,exp,_style,_power,_hp,_defense,_agile)
{
    the_type=poison;
}

void Muk::toAttack(QString &SkillName, int &hurt)
{
    int n=qrand()%3;
    switch(n)
    {
    case 0:
        SkillName="GunkShot";
        hurt=this->get_power()*3;
        break;
    case 1:
        SkillName="PosionFang";
        hurt=this->get_power()*2;
        break;
    case 2:
        SkillName="Acid Spray";
        hurt=this->get_power()*2;
        break;
    case 3:
        SkillName="Bite";
        hurt=this->get_power()*1;
        break;
    }
}




Poke_type Muk::get_type() const
{
    return the_type;
}
