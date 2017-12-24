#include "checkdialog.h"
#include "ui_checkdialog.h"

CheckDialog::CheckDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CheckDialog)
{
    ui->setupUi(this);
}

CheckDialog::~CheckDialog()
{
    delete ui;
}

void CheckDialog::on_returnBtn_clicked()
{
    this->deleteLater();
}

void CheckDialog::on_checkBtn_clicked()
{
    QString name=ui->lineEdit->text();
    if(name!="")
    {
        emit askFor(name);
    }
}

void CheckDialog::show_result(QString name)
{
    ui->label->setText(name);
}

