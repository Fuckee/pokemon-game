#ifndef PRIMEAPE_H
#define PRIMEAPE_H


#include"all_head.h"

class Primeape : public pokemon
{
public:
    Primeape(pokemon *parent);
    Primeape(Poke_quality a_quality);
    Primeape(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name="Primeape");
    virtual void toAttack(QString& SkillName,int& hurt) ;
    Poke_type get_type()const;
private:
    Poke_type the_type;
};

#endif // PRIMEAPE_H
