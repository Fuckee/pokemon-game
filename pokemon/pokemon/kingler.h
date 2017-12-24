#ifndef KINGLER_H
#define KINGLER_H

#include"all_head.h"
class Kingler : public pokemon
{
public:
    Kingler(pokemon *parent);
    Kingler(Poke_quality a_quality);
    Kingler(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name="Kingler");
    virtual void toAttack(QString& SkillName,int& hurt) ;
    Poke_type get_type()const;
private:
    Poke_type the_type;
};

#endif // KINGLER_H
