#ifndef INFO_H
#define INFO_H

#include <QDialog>
#include<player.h>
#include<pokemon/all_head.h>
namespace Ui {
class Info;
}
//用户信息介绍界面
class Info : public QDialog
{
    Q_OBJECT

public:
    explicit Info(player theplayer,QWidget *parent = 0);
    ~Info();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Info *ui;
};

#endif // INFO_H
