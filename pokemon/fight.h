#ifndef FIGHT_H
#define FIGHT_H

#include <QDialog>
#include"pokemon/all_head.h"
#include<QPropertyAnimation>
#include"theshare.h"
namespace Ui {
class Fight;
}
//精灵对战界面
class Fight : public QDialog
{
    Q_OBJECT

public:
    explicit Fight(bool type ,pokemon*,pokemon*,QDialog *parent = 0);
    ~Fight();
    void fighting(pokemon*,pokemon*);
signals:
    void gg();
    void win(bool);

private slots:


    void on_start_clicked();
    void result(bool);

private:
    Ui::Fight *ui;
    pokemon* mypoke;
    pokemon* compoke;
    QMap<QString,Poke_quality> stringToPokeQuality;
    QMap<QString,Quality> stringToQuality;
    QPropertyAnimation* myHpAnimation;
    QPropertyAnimation* comHpAnimation;
    QPropertyAnimation* myMoveAnimation;
    QPropertyAnimation* comMoveAnimation;
    QPropertyAnimation* myDieAninmation;
    QPropertyAnimation* comDieAnimation;
    void moveMy();
    void moveCom();
    void meDie();
    void comDie();
    bool _type;
};

#endif // FIGHT_H
