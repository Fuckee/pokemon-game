#include "add_dialog.h"
#include "ui_add_dialog.h"

add_Dialog::add_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_Dialog)
{
    ui->setupUi(this);
}

add_Dialog::~add_Dialog()
{
    delete ui;
}

void add_Dialog::on_sureBtn_clicked()
{
    QString name=ui->name_edit->text();
    QString password=ui->password_edit->text();
    if(name==""||password=="")
        return;
    emit add_new(name,password);
}

void add_Dialog::on_quitBtn_clicked()
{
    this->deleteLater();
}
