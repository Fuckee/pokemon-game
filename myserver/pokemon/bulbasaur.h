#ifndef BULBASAUR_H
#define BULBASAUR_H

#include"pokemon.h"

class Bulbasaur : public pokemon
{
public:
    Bulbasaur(pokemon *parent);
protected:
    virtual void toAttack1();
    virtual void toAttack2();
private:
    Poke_type the_type;
};

#endif // BULBASAUR_H
