#include "fightchose.h"
#include "ui_fightchose.h"

FightChose::FightChose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FightChose)
{
    ui->setupUi(this);
}

FightChose::~FightChose()
{
    delete ui;
}

void FightChose::on_pushButton_clicked()
{
    //进入升级赛
    prepareFight* box=new prepareFight(0,this);
    box->show();
    connect(box,SIGNAL(gg()),this,SLOT(show()));
}

void FightChose::on_pushButton_2_clicked()
{
    //进入决斗赛
    prepareFight* box=new prepareFight(1,this);
    box->show();
    connect(box,SIGNAL(gg()),this,SLOT(show()));

}

void FightChose::on_pushButton_3_clicked()
{
    emit gg();
    this->deleteLater();
}
