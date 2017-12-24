#ifndef BULBASAUR_H
#define BULBASAUR_H

#include"all_head.h"

class Bulbasaur : public pokemon
{
public:
    Bulbasaur(pokemon *parent);
    Bulbasaur(Poke_quality a_quality);
    Bulbasaur(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name="Bulbasaur");
    virtual void toAttack(QString& SkillName,int& hurt) ;
    Poke_type get_type()const;
private:
    Poke_type the_type;
};

#endif // BULBASAUR_H
