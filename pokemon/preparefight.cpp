#include "preparefight.h"
#include "ui_preparefight.h"

prepareFight::prepareFight(bool type,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::prepareFight)
{
    ui->setupUi(this);
    initialcomlist();
    _type=type;
    prepare=0;
    ui->Go->setEnabled(false);//等待选择完才可以开始战斗
    connect(this->ui->level,SIGNAL(currentIndexChanged(int)),this,SLOT(initialcomlist()));
    ui->choseCom->hide();
}

prepareFight::~prepareFight()
{
    delete ui;
}

void prepareFight::initialcomlist()
{
    int level=ui->level->currentIndex();
    qDebug()<<level;
    comlist.clear();
    for(int i=0;i<20;i++)
    {
        pokemon* apoke=theShare::randPoke(level);
        comlist.append(apoke);
    }
    ui->choseCom->show();
}



void prepareFight::on_choseYour_clicked()
{
    ChooseToFight* chooseDialog=new ChooseToFight(theShare::userPoke,this);
    connect(chooseDialog,SIGNAL(thechose(int)),this,SLOT(set_my(int)));
    chooseDialog->show();
    prepare++;
    if(prepare==2)
        ui->Go->setEnabled(true);
}

void prepareFight::on_choseCom_clicked()
{
    ChooseToFight* chooseDialog=new ChooseToFight(comlist ,this);
    connect(chooseDialog,SIGNAL(thechose(int)),this,SLOT(set_com(int)));
    chooseDialog->show();
    prepare++;
    if(prepare==2)
        ui->Go->setEnabled(true);
}

void prepareFight::on_Go_clicked()
{
    Fight* thefight=new Fight(_type,my,com,this);
    this->hide();
    connect(thefight,SIGNAL(gg()),this,SLOT(goback()));
    thefight->show();
}

void prepareFight::on_Back_clicked()
{
     emit gg();
     qDebug()<<">>";
     this->deleteLater();
}

void prepareFight::set_my(int i)
{
    my=theShare::userPoke.at(i);
}
void prepareFight::set_com(int i)
{
    com=comlist.at(i);
}

void prepareFight::goback()
{

   emit gg();
    this->deleteLater();
}
