#include "sqldialog.h"
#include "ui_sqldialog.h"
#include<QSqlQueryModel>
#include<QSqlTableModel>
#include<QTableView>
#include<QDebug>
#include<QMessageBox>
#include<QSqlError>
#include<QSqlTableModel>
SqlDialog::SqlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SqlDialog)
{
    ui->setupUi(this);
    mydb=QSqlDatabase::addDatabase("QSQLITE","connection0");
    mydb.setDatabaseName("E:\sqlite\mydata.db");
    query=QSqlQuery(mydb);
    if(!mydb.open())//无法打开数据库报错
    {
        QMessageBox::critical(0,"cannot open","unable to setablish",QMessageBox::Cancel);

    }
    //query.exec("delete from user where PokemonNum=0");
    //query.exec("delete from user where PokemonNum=0");
   // query.exec("create table clientlist (name varchar primary key,password varchar,state int)");

    connect(ui->showBtn,SIGNAL(clicked(bool)),this,SLOT(show_database()));
    connect(this,SIGNAL(happen_error()),this,SLOT(show_error()));
    query.exec("select name from clientlist");
    while(query.next())
    {
        namelist.append(query.value(0).toString());
    }
    for(int i=0;i<namelist.count();i++)
    {
        ui->choose->addItem(namelist.at(i));
        query.exec("create table "+namelist.at(i)+" (id int primary key,name varchar,level int,exp int,style varchar,power varchar,hp varchar,"
                                                  "defense varchar,agile varchar )");
    }
   //  query.exec("alter table clientlist add win int(0) null");
  // query.exec("alter table clientlist add lose int(0) null");
 //   query.exec("alter table clientlist add numbadge varchar null");
  //  query.exec("alter table clientlist add highbadge varchar null");
   // query.exec("alter table clientlist add money int(0) null");
    query.exec("alter table clientlist add win1 int(0) null");
     query.exec("alter table clientlist add lose1 int(0) null");
    ui->choose->addItem("clientlist");
    //服务器虚拟训练师

    query.exec("create table serverlist (name varchar primary key,level varchar)");
    ui->serverchose->addItem("serverlist");
    query.exec("select name from serverlist");
    while(query.next())
    {
        serverlist.append(query.value(0).toString());
    }
    for(int i=0;i<serverlist.count();i++)
    {
        ui->serverchose->addItem(serverlist.at(i));
        query.exec("create table "+serverlist.at(i)+" (id int primary key,name varchar,level int,style varchar,power varchar,hp varchar,"
                                                  "defense varchar,agile varchar )");//   无经验属性
    }
    //query.exec("delete from clientlist where name='tian'");
   // query.exec("delete from clientlist where name='song'");
   // query.exec("delete from clientlist where name='qq'");
   // query.exec("delete from clientlist where name='zzr'");
    //query.exec("drop table tian");
   // query.exec("drop table song");
   // query.exec("drop table qq");
   // query.exec("drop table zzr");
}

SqlDialog::~SqlDialog()
{
    delete ui;
}
void SqlDialog::show_database()//可视化选中的数据库
{
    QString chose=ui->choose->currentText();
    //QSqlQueryModel *model=new QSqlQueryModel(this);
    //model->setQuery("select * from user ");
   // model->setHeaderData(0,Qt::Horizontal,"序号");
   // model->setHeaderData(1,Qt::Horizontal,"姓名");
    //model->setHeaderData(2,Qt::Horizontal,"密码");
    //ui->tableView->setModel(model);
    //setCentralWidget(view);
    QSqlTableModel* model;
    model=new QSqlTableModel(this,mydb);
    model->setTable(chose);
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setModel(model);
}

void SqlDialog::show_error()
{
    ui->errorlist->addItem(query.lastError().text());
}

void SqlDialog::addNew( QString name, QString password)
{
    query.exec("select * from clientlist");
    query.prepare("insert into clientlist(name,password,state,win,lose,numbadge,highbadge,win1,lose1)values(:name,:password,:state,:win,:lose,:numbadge,:highbadge,:win1,:lose1)");
    query.bindValue(":name",name);
    query.bindValue(":password",password);
    query.bindValue(":state",0);
    query.bindValue(":win",0);
    query.bindValue(":lose",0);
    query.bindValue(":numbadge","null");
    query.bindValue(":highbadge","null");
    query.bindValue(":win1",0);
    query.bindValue(":lose1",0);
    if(!query.exec())
    {
        emit happen_error();
    }
}

void SqlDialog::on_addBtn_clicked()
{
      QString chose=ui->choose->currentText();
      if(chose=="clientlist")
      {
          Add_Dialog=new add_Dialog(this);
          //this->hide();
          connect(Add_Dialog,SIGNAL(add_new(QString,QString)),this,SLOT(addNew(QString,QString)));
          connect(Add_Dialog,SIGNAL(add_new(QString,QString)),Add_Dialog,SLOT(deleteLater()));
          Add_Dialog->show();

      }
      else
      {
          addPokemon=new AddPokemon(this,namelist);
          connect(addPokemon,SIGNAL(add(QString,QString,int,int,QString,QString,QString,QString,QString)),this,SLOT(addPoke(QString,QString,int,int,QString,QString,QString,QString,QString)));
          addPokemon->show();
      }


}



void SqlDialog::on_pushButton_clicked()
{
    Del_Dialog=new DeleteDialog(this);
    connect(Del_Dialog,SIGNAL(deleteID(QString)),this,SLOT(deleteID(QString)));
    Del_Dialog->show();
}

void SqlDialog::deleteID(QString i)
{
    if(!query.exec("delete from clientlist where name='"+i+"'"))
    {
        emit happen_error();
    }
}

void SqlDialog::checkPassword(QString name)
{
    if(!query.exec("SELECT password FROM clientlist where name='"+name+"'"))
    {
        emit happen_error();
        return;
    }
    query.next();
    QString result=query.value(0).toString();
    ui->debug->setText(result);
    emit returnPassword(result);

}
//id int primary key,name varchar,level int,exp int,style varchar,power varchar,hp varchar,defense varchar,agile varchar
void SqlDialog::addPoke(QString user, QString name,int level,int exp, QString style,QString power,QString hp,QString defense,QString agile)
{
    query.exec("select * from "+user);
    int num=0;
    while(query.next())
    {
        num++;
    }
    query.prepare("insert into "+user+"(id,name,level,exp,style,power,hp,defense,agile)"
                                      "values(:id,:name,:level,:exp,:style,:power,:hp,:defense,:agile)");
    query.bindValue(":id",num+1);
    query.bindValue(":name",name);
    query.bindValue(":level",level);
    query.bindValue(":exp",exp);
    query.bindValue(":style",style);
    query.bindValue(":power",power);
    query.bindValue(":hp",hp);
    query.bindValue(":defense",defense);
    query.bindValue(":agile",agile);
    if(!query.exec())
    {
        emit happen_error();
    }
}

void SqlDialog::addServer(QString name, QString level)
{
    query.prepare("insert into serverlist(name,level)values(:name,:level)");
    query.bindValue(":name",name);
    query.bindValue(":level",level);
    if(!query.exec())
    {
        emit happen_error();
    }
}

void SqlDialog::AddServerPoke(QString user, QString name, int level, QString style,QString power,QString hp,QString defense,QString agile)
{
    query.exec("select * from "+user);
    int num=0;
    while(query.next())
    {
        num++;
    }
    query.prepare("insert into "+user+"(id,name,level,style,power,hp,defense,agile)"
                                      "values(:id,:name,:level,:style,:power,:hp,:defense,:agile)");
    query.bindValue(":id",num+1);
    query.bindValue(":name",name);
    query.bindValue(":level",level);
    query.bindValue(":style",style);
    query.bindValue(":power",power);
    query.bindValue(":hp",hp);
    query.bindValue(":defense",defense);
    query.bindValue(":agile",agile);
    if(!query.exec())
    {
        emit happen_error();
    }
}



void SqlDialog::on_checkBtn_clicked()
{
    checkDialog=new CheckDialog(this);
    checkDialog->show();
    connect(checkDialog,SIGNAL(askFor(QString)),this,SLOT(checkPassword(QString)));
    connect(this,SIGNAL(returnPassword(QString)),checkDialog,SLOT(show_result(QString)));
}

void SqlDialog::on_returnBtn_clicked()
{
    mydb.close();
    this->deleteLater();
}

void SqlDialog::on_serveraddbtn_clicked()
{
    QString chose=ui->serverchose->currentText();
    if(chose=="serverlist")
    {
        serverAdd* ServerAdd=new serverAdd(this);
        connect(ServerAdd,SIGNAL(addServer(QString,QString)),this,SLOT(addServer(QString,QString)));
        ServerAdd->show();
    }
    else
    {
        addServerPoke* serverPokeAdd=new addServerPoke(serverlist,this);
        connect(serverPokeAdd,SIGNAL(add(QString,QString,int,QString,QString,QString,QString,QString)),this,SLOT(AddServerPoke(QString,QString,int,QString,QString,QString,QString,QString)));
        serverPokeAdd->show();
    }
}

void SqlDialog::on_show2_clicked()
{
    QString chose=ui->serverchose->currentText();
    //QSqlQueryModel *model=new QSqlQueryModel(this);
    //model->setQuery("select * from user ");
   // model->setHeaderData(0,Qt::Horizontal,"序号");
   // model->setHeaderData(1,Qt::Horizontal,"姓名");
    //model->setHeaderData(2,Qt::Horizontal,"密码");
    //ui->tableView->setModel(model);
    //setCentralWidget(view);
    QSqlTableModel* model;
    model=new QSqlTableModel(this,mydb);
    model->setTable(chose);
    model->select();
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    ui->tableView->setModel(model);
}
