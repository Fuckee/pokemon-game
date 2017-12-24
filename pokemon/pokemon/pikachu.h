#ifndef PIKACHU_H
#define PIKACHU_H


#include"all_head.h"

class Pikachu : public pokemon
{
public:
    Pikachu(pokemon *parent);
    Pikachu(Poke_quality a_quality);
    Pikachu(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name="Pikachu");
    virtual void toAttack(QString& SkillName,int& hurt) ;
    Poke_type get_type()const;
private:
    Poke_type the_type;
};

#endif // PIKACHU_H
