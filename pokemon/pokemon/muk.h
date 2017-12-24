#ifndef MUK_H
#define MUK_H


#include"all_head.h"

class Muk : public pokemon
{
public:
    Muk(pokemon *parent);
    Muk(Poke_quality a_quality);
    Muk(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name="Muk");
    virtual void toAttack(QString& SkillName,int& hurt) ;
    Poke_type get_type()const;
private:
    Poke_type the_type;
};

#endif // MUK_H
