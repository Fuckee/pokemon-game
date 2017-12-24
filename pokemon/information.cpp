#include "information.h"
#include "ui_information.h"

Information::Information(pokemon* poke,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Information)
{
    ui->setupUi(this);
    QString name="  "+poke->get_name();
    ui->name->setText(name);

    QString level="   "+QString::number(poke->get_level());
    ui->level->setText(level);

    Poke_quality _style=poke->get_style();
    QString style=theShare::PokeQualityToString[_style];
    ui->type->setText(style);

    int _power=poke->get_power();
    int _hp=poke->get_hp();
    int _defense=poke->get_defense();
    int _attackInterval=poke->get_attack_interval();
    QString power="Power:"+QString::number(_power);
    QString hp="Hp:"+QString::number(_hp);
    QString defense="Defend:"+QString::number(_defense);
    QString attackInterval="Attack Shot:"+QString::number(_attackInterval);
    ui->power->setText(power);
    ui->hp->setText(hp);
    ui->defend->setText(defense);
    ui->attackInterval->setText(attackInterval);
    //border-image: url(:/image/Pidgeotto.png);
    name=poke->get_name();
    QString styleSheet="border-image: url(:/image/"+name+".png);";
    ui->label_2->setStyleSheet(styleSheet);

}

Information::~Information()
{
    delete ui;
}

void Information::on_pushButton_clicked()
{
    this->deleteLater();
}
