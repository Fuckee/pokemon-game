#ifndef DIALOG_H
#define DIALOG_H
#include"server.h"
#include <QDialog>
#include<QTcpServer>
#include<QGridLayout>
#include<QPushButton>
#include<QListWidget>
#include"add_dialog.h"
#include"checkdialog.h"
#include"deletedialog.h"
#include"sqldialog.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    int port;
    server*  myserver;    
    int connect_num;

public slots:
    void createServer();
    void have_new();//有新的尝试连接
    void have_newsucess(QString);//连接成功
    void have_newstop(QString);//有连接断开了
    void connect_num_increase();
    void connect_num_decrease();
    void showlist_num();
private slots:
    void on_openSql_clicked();
};


#endif // DIALOG_H
