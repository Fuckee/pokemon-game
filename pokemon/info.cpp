#include "info.h"
#include "ui_info.h"

Info::Info(player  aplayer,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
    QString name=aplayer.name;
    ui->name->setText(name);
    int _win,_win1,_lose,_lose1;
    _win=aplayer.win;
    _win1=aplayer.win1;
    _lose=aplayer.lose;
    _lose1=aplayer.lose1;
    int _state=aplayer.state;
    QString _numbadge=aplayer.numbadge,_highbadge=aplayer.highbadge;
    //border-image: url(:/images/gold.png);
    QString numbadge="border-image: url(:/images/"+_numbadge+".png);";
    QString highbadge="border-image: url(:/images/"+_highbadge+".png);";
    ui->highbadge->setStyleSheet(highbadge);
    ui->numbadge->setStyleSheet(numbadge);
    QString state;
    if(_state==1)
    {
        state="Online";
    }
    else
    {
        state="Leave";
    }
    ui->state->setText(state);
    QString win,win1,lose,lose1;
    win=QString::number(_win);
    lose=QString::number(_lose);
    win1=QString::number(_win1);
    lose1=QString::number(_lose1);
    ui->win->setText(win);
    ui->win1->setText(win1);
    ui->lose->setText(lose);
    ui->lose1->setText(lose1);
    float _rate;
    if(_win+_lose==0)
    {
        _rate=0;
    }
    else
        _rate=(float)_win/((float)_win+(float)_lose);
    _rate=_rate*100;
    int __rate=(int)_rate;
    float _rate1;
    if(_win1+_lose1==0)
    {
        _rate1=0;
    }
    else
        _rate1=(float)_win1/((float)_win1+(float)_lose1);
    _rate1=_rate1*100;
    int __rate1=(int)_rate1;
    QString rate="rate:"+QString::number(__rate)+"%";

    QString rate1="rate:"+QString::number(__rate1)+"%";
    ui->rate->setText(rate);
    ui->rate1->setText(rate1);

}

Info::~Info()
{
    delete ui;
}

void Info::on_pushButton_clicked()
{
    this->deleteLater();
}
