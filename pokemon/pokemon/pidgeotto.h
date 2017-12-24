#ifndef PIDGEOTTO_H
#define PIDGEOTTO_H


#include"all_head.h"

class Pidgeotto : public pokemon
{
public:
    Pidgeotto(pokemon *parent);
    Pidgeotto(Poke_quality a_quality);
    Pidgeotto(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name="Pidgeotto");
    virtual void toAttack(QString& SkillName,int& hurt) ;
    Poke_type get_type()const;
private:
    Poke_type the_type;
};

#endif // PIDGEOTTO_H
