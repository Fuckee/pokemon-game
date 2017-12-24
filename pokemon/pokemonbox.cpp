#include "pokemonbox.h"
#include "ui_pokemonbox.h"

PokemonBox::PokemonBox(QList<pokemon*>list,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PokemonBox)
{
    ui->setupUi(this);
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
    //
    pokelist=list;
    connect(this,SIGNAL(clickN(int)),this,SLOT(showPoke(int)));
    for(int i=0;i<pokelist.count();i++)
    {
        pokemon* apoke=pokelist.at(i);
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

PokemonBox::~PokemonBox()
{
    delete ui;
}



void PokemonBox::on_a2_clicked()
{
    emit clickN(2);
}

void PokemonBox::on_a1_clicked()
{
    emit clickN(1);
}

void PokemonBox::on_a3_clicked()
{
    emit clickN(3);
}

void PokemonBox::on_a4_clicked()
{
    emit clickN(4);
}

void PokemonBox::on_a5_clicked()
{
    emit clickN(5);
}

void PokemonBox::on_a6_clicked()
{
    emit clickN(6);
}

void PokemonBox::on_a7_clicked()
{
    emit clickN(7);
}



void PokemonBox::on_a8_clicked()
{
    emit clickN(8);
}

void PokemonBox::on_a10_clicked()
{
    emit clickN(10);
}

void PokemonBox::on_a11_clicked()
{
    emit clickN(11);
}

void PokemonBox::on_a12_clicked()
{
    emit clickN(12);
}

void PokemonBox::on_a13_clicked()
{
    emit clickN(13);
}

void PokemonBox::on_a14_clicked()
{
    emit clickN(14);
}

void PokemonBox::on_a15_clicked()
{
    emit clickN(15);
}

void PokemonBox::on_a16_clicked()
{
    emit clickN(16);
}

void PokemonBox::on_a17_clicked()
{
    emit clickN(17);
}

void PokemonBox::on_a18_clicked()
{
    emit clickN(18);
}

void PokemonBox::on_a19_clicked()
{
    emit clickN(19);
}

void PokemonBox::on_a20_clicked()
{
    emit clickN(20);
}

void PokemonBox::on_a21_clicked()
{
    emit clickN(21);
}

void PokemonBox::on_a22_clicked()
{
    emit clickN(22);
}

void PokemonBox::on_a23_clicked()
{
    emit clickN(23);
}

void PokemonBox::on_a24_clicked()
{
    emit clickN(24);
}

void PokemonBox::on_a25_clicked()
{
    emit clickN(25);
}

void PokemonBox::on_a26_clicked()
{
    emit clickN(26);
}

void PokemonBox::on_a27_clicked()
{
    emit clickN(27);
}

void PokemonBox::on_a28_clicked()
{
    emit clickN(28);
}

void PokemonBox::on_a29_clicked()
{
    emit clickN(29);
}

void PokemonBox::on_a30_clicked()
{
    emit clickN(30);
}

void PokemonBox::showPoke(int i)
{
    pokemon* thepoke=pokelist.at(i-1);
    Information* info=new Information(thepoke,this);
    info->show();
}

void PokemonBox::on_a9_clicked()
{
    emit clickN(9);
}

void PokemonBox::on_pushButton_clicked()
{
    this->deleteLater();
}
