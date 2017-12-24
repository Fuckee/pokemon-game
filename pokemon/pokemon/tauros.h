#ifndef TAUROS_H
#define TAUROS_H


#include"all_head.h"

class Tauros : public pokemon
{
public:
    Tauros(pokemon *parent);
    Tauros(Poke_quality a_quality);
    Tauros(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name="Tauros");
    virtual void toAttack(QString& SkillName,int& hurt) ;
    Poke_type get_type()const;
private:
    Poke_type the_type;
};

#endif // TAUROS_H
