#include "dialog.h"
#include "ui_dialog.h"
#include"server.h"
#include<QLabel>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    port=8086;
    connect(ui->createBtn,SIGNAL(clicked()),this,SLOT(createServer()));
    connect_num=0;
    ui->debugBtn->setEnabled(false);
    setWindowTitle("people online:"+QString::number(connect_num,10));
}
void Dialog::showlist_num()
{
    int i=myserver->SocketList.count();
    ui->mylist->addItem(QString::number(i,10));
}

void Dialog::connect_num_increase()
{
    connect_num+=1;
    setWindowTitle("people online:"+QString::number(connect_num,10));
}

void Dialog::connect_num_decrease()
{
    connect_num-=1;
    setWindowTitle("people online:"+QString::number(connect_num,10));
}

Dialog::~Dialog()
{
    delete ui;
}



void Dialog::createServer()
{
    myserver=new server();
    ui->createBtn->setEnabled(false);
    connect(myserver,SIGNAL(new_connect()),this,SLOT(have_new()));
    connect(myserver,SIGNAL(show_connect_stop(QString)),this,SLOT(have_newstop(QString)));
    connect(myserver,SIGNAL(show_connect_stop(QString)),this,SLOT(connect_num_decrease()));
    connect(myserver,SIGNAL(new_connect_success(QString)),this,SLOT(connect_num_increase()));
    connect(myserver,SIGNAL(new_connect_success(QString)),this,SLOT(have_newsucess(QString)));
    ui->debugBtn->setEnabled(true);
    connect(ui->debugBtn,SIGNAL(clicked()),this,SLOT(showlist_num()));
}
void Dialog::have_newsucess(QString id)
{
    ui->mylist->addItem(id+"connect successful");
}

void Dialog::have_newstop(QString id)
{
    ui->mylist->addItem(id+"leave");
}

void Dialog::have_new()
{
    ui->mylist->addItem("new connection");
}


void Dialog::on_openSql_clicked()
{
    SqlDialog* sqlDialog=new SqlDialog(this);
    sqlDialog->show();
}
