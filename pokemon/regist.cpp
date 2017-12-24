#include "regist.h"
#include "ui_regist.h"

Regist::Regist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Regist)
{
    ui->setupUi(this);
}

Regist::~Regist()
{
    delete ui;
}

void Regist::on_sure_clicked()
{
    QString name=ui->id->text();
    QString pw=ui->pw->text();
    emit registNew(name,pw);
    this->deleteLater();
}
