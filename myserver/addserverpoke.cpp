#include "addserverpoke.h"
#include "ui_addserverpoke.h"

addServerPoke::addServerPoke(QStringList list,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addServerPoke)
{
    ui->setupUi(this);
    for(int i=0;i<list.count();i++)
    {
        ui->list_2->addItem(list.at(i));
    }
}

addServerPoke::~addServerPoke()
{
    delete ui;
}

void addServerPoke::on_sureBtn_clicked()
{
    QString user=ui->list_2->currentText();
    QString name=ui->name_2->currentText();
    int level=ui->level_2->currentData().toInt();
    QString style=ui->style_2->currentText();
    QString power=ui->power_2->currentText();
    QString hp=ui->hp_2->currentText();
    QString defense=ui->defense_2->currentText();
    QString agile=ui->agile_2->currentText();
    emit add(user,name,level,style,power,hp,defense,agile);
    this->deleteLater();
}
