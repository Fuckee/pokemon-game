#include "bulbasaur.h"
#include"type.h"


Bulbasaur::Bulbasaur(pokemon *parent):pokemon(parent)
{
    this->set_name("Bulbasaur");
    the_type=glass;
}



void Bulbasaur::toAttack1()
{
    qDebug()<<"tengbiangongji";
}

void Bulbasaur::toAttack2()
{
    qDebug()<<"yangguanglieyan";
}

