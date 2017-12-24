#ifndef CHARMANDER_H
#define CHARMANDER_H

#include"all_head.h"
class pokemon;
class Charmander : public pokemon
{
public:
    Charmander(pokemon *parent);
    Charmander(Poke_quality a_quality);
    Charmander(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name="Charmander");
    virtual void toAttack(QString& SkillName,int& hurt) ;
    Poke_type get_type()const;
private:
    Poke_type the_type;
};

#endif // CHARMANDER_H
