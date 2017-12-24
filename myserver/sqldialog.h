#ifndef SQLDIALOG_H
#define SQLDIALOG_H

#include <QDialog>

#include <QMainWindow>
#include<QMessageBox>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include<QSqlRecord>
#include<QSqlTableModel>
#include<QTableView>
#include<QDebug>
#include<QMessageBox>
#include<QSqlError>
#include<QSqlQueryModel>
#include<QMainWindow>
#include<QObject>
#include"add_dialog.h"
#include"deletedialog.h"
#include"checkdialog.h"
#include"addpokemon.h"
#include"serveradd.h"
#include"addserverpoke.h"
namespace Ui {
class SqlDialog;
}

class SqlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SqlDialog(QWidget *parent = 0);
    ~SqlDialog();

private:
    Ui::SqlDialog *ui;
signals:
    void happen_error();
    void returnPassword(QString);
private slots:
    void on_addBtn_clicked();
    void show_database();
    void show_error();
    void on_pushButton_clicked();
;

    void on_checkBtn_clicked();

    void on_returnBtn_clicked();

    void on_serveraddbtn_clicked();

    void on_show2_clicked();

public slots:
    void addNew(QString name,QString password);
    void deleteID(QString);
    void checkPassword(QString);
    void addPoke(QString ,QString,int,int,QString,QString,QString,QString,QString);
    void addServer(QString ,QString);
    void AddServerPoke(QString,QString,int,QString,QString,QString,QString,QString);

private:
    QSqlDatabase mydb;
    QSqlQuery query;
    add_Dialog* Add_Dialog;
    DeleteDialog* Del_Dialog;
    CheckDialog*  checkDialog;
    AddPokemon* addPokemon;
    QStringList namelist;
    QStringList serverlist;//虚拟训练师名单
};

#endif // SQLDIALOG_H
