#include "twochoose.h"
#include "ui_twochoose.h"
#include "pokemonbox.h"
#include "info.h"
TwoChoose::TwoChoose(player aplayer,QList<pokemon*> list,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TwoChoose)
{
    ui->setupUi(this);
   // abox=new PokemonBox(list,this);
     //info=new Info(aplayer,this);
    _player=aplayer;
    pokelist=list;
}

TwoChoose::~TwoChoose()
{
    delete ui;
}

void TwoChoose::on_pushButton_2_clicked()//选择查看信息
{
     Info* theinfo=new Info(_player,this);
     theinfo->show();
}

void TwoChoose::on_pushButton_3_clicked()//选择查看精灵
{
    PokemonBox* thebox=new PokemonBox(pokelist,this);
    thebox->show();
    //abox->show();
}

void TwoChoose::on_pushButton_clicked()//返回
{
    emit gg();
    this->deleteLater();
}
