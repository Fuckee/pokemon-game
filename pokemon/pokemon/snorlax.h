#ifndef SNORLAX_H
#define SNORLAX_H


#include"all_head.h"

class Snorlax : public pokemon
{
public:
    Snorlax(pokemon *parent);
    Snorlax(Poke_quality a_quality);
    Snorlax(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name="Snorlax");
    virtual void toAttack(QString& SkillName,int& hurt) ;
    Poke_type get_type()const;
private:
    Poke_type the_type;
};

#endif // SNORLAX_H
