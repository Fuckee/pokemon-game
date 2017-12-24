#ifndef LAPRAS_H
#define LAPRAS_H


#include"all_head.h"

class Lapras : public pokemon
{
public:
    Lapras(pokemon *parent);
    Lapras(Poke_quality a_quality);
    Lapras(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name="Lapras");
    virtual void toAttack(QString& SkillName,int& hurt) ;
    Poke_type get_type()const;
private:
    Poke_type the_type;
};

#endif // LAPRAS_H
