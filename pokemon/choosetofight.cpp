#include "choosetofight.h"
#include "ui_choosetofight.h"

ChooseToFight::ChooseToFight(QList<pokemon*> list,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseToFight)
{
    ui->setupUi(this);
    thelist=list;
    if(1)
    {
        ui->a1->setEnabled(false);
        ui->a2->setEnabled(false);
        ui->a3->setEnabled(false);
        ui->a4->setEnabled(false);
        ui->a5->setEnabled(false);
        ui->a6->setEnabled(false);
        ui->a7->setEnabled(false);
        ui->a8->setEnabled(false);
        ui->a9->setEnabled(false);
        ui->a10->setEnabled(false);
        ui->a11->setEnabled(false);
        ui->a12->setEnabled(false);
        ui->a13->setEnabled(false);
        ui->a14->setEnabled(false);
        ui->a15->setEnabled(false);
        ui->a16->setEnabled(false);
        ui->a17->setEnabled(false);
        ui->a18->setEnabled(false);
        ui->a19->setEnabled(false);
        ui->a20->setEnabled(false);
        ui->a21->setEnabled(false);
        ui->a22->setEnabled(false);
        ui->a23->setEnabled(false);
        ui->a24->setEnabled(false);
        ui->a25->setEnabled(false);
        ui->a26->setEnabled(false);
        ui->a27->setEnabled(false);
        ui->a28->setEnabled(false);
        ui->a29->setEnabled(false);
        ui->a30->setEnabled(false);
    }
    for(int i=0;i<thelist.count();i++)
    {
        pokemon* apoke=thelist.at(i);
        if(i==0)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a1->setStyleSheet(word);
            ui->a1->setEnabled(true);
        }
        else if(i==1)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a2->setStyleSheet(word);
            ui->a2->setEnabled(true);
        }
        else if(i==2)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a3->setStyleSheet(word);
            ui->a3->setEnabled(true);
        }
        else if(i==3)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a4->setStyleSheet(word);
            ui->a4->setEnabled(true);
        }
        else if(i==4)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a5->setStyleSheet(word);ui->a5->setEnabled(true);
        }
        else if(i==5)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a6->setStyleSheet(word);ui->a6->setEnabled(true);
        }
        else if(i==6)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a7->setStyleSheet(word);ui->a7->setEnabled(true);
        }
        else if(i==7)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a8->setStyleSheet(word);ui->a8->setEnabled(true);
        }
        else if(i==8)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a9->setStyleSheet(word);ui->a9->setEnabled(true);
        }
        else if(i==9)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a10->setStyleSheet(word);ui->a10->setEnabled(true);
        }
        else if(i==10)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a11->setStyleSheet(word);ui->a11->setEnabled(true);
        }
        else if(i==11)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a12->setStyleSheet(word);ui->a12->setEnabled(true);
        }
        else if(i==12)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a13->setStyleSheet(word);ui->a13->setEnabled(true);
        }
        else if(i==13)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a14->setStyleSheet(word);ui->a14->setEnabled(true);
        }
        else if(i==14)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a15->setStyleSheet(word);ui->a15->setEnabled(true);
        }
        else if(i==15)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a16->setStyleSheet(word);ui->a16->setEnabled(true);
        }
        else if(i==16)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a17->setStyleSheet(word);ui->a17->setEnabled(true);
        }
        else if(i==17)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a18->setStyleSheet(word);ui->a18->setEnabled(true);
        }
        else if(i==18)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a19->setStyleSheet(word);ui->a19->setEnabled(true);
        }
        else if(i==19)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a20->setStyleSheet(word);ui->a20->setEnabled(true);
        }
        else if(i==20)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a21->setStyleSheet(word);ui->a21->setEnabled(true);
        }
        else if(i==21)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a22->setStyleSheet(word);ui->a22->setEnabled(true);
        }
        else if(i==22)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a23->setStyleSheet(word);ui->a23->setEnabled(true);
        }
        else if(i==23)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a24->setStyleSheet(word);ui->a24->setEnabled(true);
        }
        else if(i==24)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a25->setStyleSheet(word);ui->a25->setEnabled(true);
        }
        else if(i==25)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a26->setStyleSheet(word);ui->a26->setEnabled(true);
        }
        else if(i==26)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a27->setStyleSheet(word);ui->a27->setEnabled(true);
        }
        else if(i==27)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a28->setStyleSheet(word);ui->a28->setEnabled(true);
        }
        else if(i==28)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a29->setStyleSheet(word);ui->a29->setEnabled(true);
        }
        else if(i==29)
        {
            QString name=apoke->get_name();
            QString word="border-image: url(:/image/"+name+".png);";
            ui->a30->setStyleSheet(word);ui->a30->setEnabled(true);
        }
    }
}

ChooseToFight::~ChooseToFight()
{
    delete ui;
}

void ChooseToFight::on_a1_clicked()
{
    emit thechose(0);
    this->deleteLater();

}

void ChooseToFight::on_a2_clicked()
{
    emit thechose(1);
    this->deleteLater();

}
void ChooseToFight::on_a3_clicked()
{
    emit thechose(2);
    this->deleteLater();

}
void ChooseToFight::on_a4_clicked()
{
    emit thechose(3);
    this->deleteLater();

}
void ChooseToFight::on_a5_clicked()
{
    emit thechose(4);
    this->deleteLater();

}
void ChooseToFight::on_a6_clicked()
{
    emit thechose(5);
    this->deleteLater();

}
void ChooseToFight::on_a7_clicked()
{
    emit thechose(6);
    this->deleteLater();

}
void ChooseToFight::on_a8_clicked()
{
    emit thechose(7);
    this->deleteLater();

}
void ChooseToFight::on_a9_clicked()
{
    emit thechose(8);
    this->deleteLater();

}
void ChooseToFight::on_a10_clicked()
{
    emit thechose(9);
    this->deleteLater();

}
void ChooseToFight::on_a11_clicked()
{
    emit thechose(10);
    this->deleteLater();

}
void ChooseToFight::on_a12_clicked()
{
    emit thechose(11);
    this->deleteLater();

}
void ChooseToFight::on_a13_clicked()
{
    emit thechose(12);
    this->deleteLater();

}
void ChooseToFight::on_a14_clicked()
{
    emit thechose(13);
    this->deleteLater();

}
void ChooseToFight::on_a15_clicked()
{
    emit thechose(14);
    this->deleteLater();

}
void ChooseToFight::on_a16_clicked()
{
    emit thechose(15);
    this->deleteLater();

}
void ChooseToFight::on_a17_clicked()
{
    emit thechose(16);
    this->deleteLater();

}
void ChooseToFight::on_a18_clicked()
{
    emit thechose(17);
    this->deleteLater();

}
void ChooseToFight::on_a19_clicked()
{
    emit thechose(18);
    this->deleteLater();

}
void ChooseToFight::on_a20_clicked()
{
    emit thechose(19);
    this->deleteLater();

}
void ChooseToFight::on_a21_clicked()
{
    emit thechose(20);
    this->deleteLater();

}
void ChooseToFight::on_a22_clicked()
{
    emit thechose(21);
    this->deleteLater();

}

