#ifndef SQUIRTLE_H
#define SQUIRTLE_H



#include"all_head.h"
class pokemon;
class Squirtle : public pokemon
{
public:
    Squirtle(pokemon *parent);
    Squirtle(Poke_quality a_quality);
    Squirtle(int level, int exp, Poke_quality _style, Quality _power, Quality _hp, Quality _defense, Quality _agile,QString name="Squirtle");
    virtual void toAttack(QString& SkillName,int& hurt);

    Poke_type get_type()const;
private:
    Poke_type the_type;
};

#endif // SQUIRTLE_H
