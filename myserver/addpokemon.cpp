#include "addpokemon.h"
#include "ui_addpokemon.h"

AddPokemon::AddPokemon(QWidget* parent,QStringList list) :
    QDialog(parent),
    ui(new Ui::AddPokemon)
{
    ui->setupUi(this);
    namelist=list;
    for(int i=0;i<namelist.count();i++)
    {
        ui->list->addItem(list.at(i));
    }
}

AddPokemon::~AddPokemon()
{
    delete ui;
}

void AddPokemon::on_level_currentIndexChanged(int index)
{
    ui->exp->clear();
    for(int i=0;i<=(index+1)*10;i++)
    {
        ui->exp->addItem(QString::number(i));
    }
}



void AddPokemon::on_backBtn_clicked()
{
    this->deleteLater();
}

void AddPokemon::on_sureBtn_clicked()
{
    QString user=ui->list->currentText();
    QString name=ui->name->currentText();
    int level=ui->level->currentText().toInt();
    int exp=ui->exp->currentData().toInt();
    QString style=ui->style->currentText();
    QString power=ui->power->currentText();
    QString hp=ui->hp->currentText();
    QString defense=ui->defense->currentText();
    QString agile=ui->agile->currentText();
    emit add(user,name,level,exp,style,power,hp,defense,agile);
    this->deleteLater();
}
