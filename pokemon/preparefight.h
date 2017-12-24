#ifndef PREPAREFIGHT_H
#define PREPAREFIGHT_H

#include <QDialog>
#include"pokemon/all_head.h"
#include"choosetofight.h"
#include"theshare.h"
#include"fight.h"
namespace Ui {
class prepareFight;
}
//战斗准备界面
class prepareFight : public QDialog
{
    Q_OBJECT

public:
    explicit prepareFight(bool type,QWidget *parent = 0);
    ~prepareFight();

signals:
    void gg();
private slots:


    void on_choseCom_clicked();

    void on_choseYour_clicked();

    void on_Go_clicked();

    void on_Back_clicked();
    void set_my(int);//选择我方精灵
    void set_com(int);//选择电脑出站精灵
    void goback();
    void initialcomlist();//初始化对战精灵列表

private:
    Ui::prepareFight *ui;
    bool _type;//0为升级，1为决斗
    pokemon* com;//对手精灵
    pokemon* my;//我方精灵
    QList<pokemon*> comlist;//对战精灵列表
    int prepare;//当选择完成才使战斗按钮有效


};

#endif // PREPAREFIGHT_H
