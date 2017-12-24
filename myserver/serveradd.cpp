#include "serveradd.h"
#include "ui_serveradd.h"

serverAdd::serverAdd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::serverAdd)
{
    ui->setupUi(this);
}

serverAdd::~serverAdd()
{
    delete ui;
}

void serverAdd::on_pushButton_clicked()
{
    QString name=ui->name->text();
    QString level=ui->level->currentText();
    emit addServer(name,level);
    this->deleteLater();
}
