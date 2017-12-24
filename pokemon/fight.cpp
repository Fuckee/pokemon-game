#include "fight.h"
#include "ui_fight.h"
#include<QTest>
#define interval 3000//战斗间隔
#define hpAnimation 1000//动画间隔
#define avoidrate 15//躲避几率%
#define critrate 60//暴击几率%
Fight::Fight(bool type,pokemon* a,pokemon* b,QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Fight)
{
    ui->setupUi(this);
    mypoke=a;//我方精灵
    compoke=b;//地方精灵
    _type=type;//战斗类型 分为决斗赛 和 升级赛
    connect(this,SIGNAL(win(bool)),this,SLOT(result(bool)));
    //初始化MAP
    stringToPokeQuality.insert("hpful",hpful);
    stringToPokeQuality.insert("defendful",defendful);
    stringToPokeQuality.insert("fast",fast);
    stringToPokeQuality.insert("strong",strong);
    stringToQuality.insert("excellent",excellent);
    stringToQuality.insert("great",great);
    stringToQuality.insert("normal",normal);
    stringToQuality.insert("bad",bad);
    //初始化动画机
    myHpAnimation=new QPropertyAnimation(ui->myHP,"value");
    comHpAnimation=new QPropertyAnimation(ui->comHP,"value");
    myMoveAnimation=new QPropertyAnimation(ui->myphoto,"geometry");
    myMoveAnimation->setEasingCurve(QEasingCurve::Linear);
    comMoveAnimation=new QPropertyAnimation(ui->comphoto,"geometry");
    comMoveAnimation->setEasingCurve(QEasingCurve::InQuint);
    myHpAnimation->setEasingCurve(QEasingCurve::Linear);
    comHpAnimation->setEasingCurve(QEasingCurve::Linear);
    myDieAninmation=new QPropertyAnimation(ui->myphoto,"geometry");
    comDieAnimation=new QPropertyAnimation(ui->comphoto,"geometry");
    myDieAninmation->setEasingCurve(QEasingCurve::Linear);
    comDieAnimation->setEasingCurve(QEasingCurve::Linear);
}

Fight::~Fight()//析构函数
{
    delete ui;
}
void Fight::fighting(pokemon *my, pokemon *com)//实现对战函数
{
    qDebug()<<com->get_power();
  //  ui->war->show();
    //initial hp bar
    int my_hp=my->get_hp();
    int com_hp=com->get_hp();
    ui->myHP->setMaximum(my_hp);
    ui->myHP->setValue(my_hp);
    ui->comHP->setStyleSheet("color: rgb(0, 255, 0);");
    ui->comHP->setMaximum(com_hp);
    ui->comHP->setValue(com_hp);
    //set pokemon photo name level
    int mylevel=my->get_level();
    int comlevel=com->get_level();
    ui->mylevel->setText(QString::number(mylevel));
    ui->comlevel->setText(QString::number(comlevel));
   // ":/image/Bulbasaur.png"
    QString _myphoto="border-image: url(:/image/"+my->get_name()+"1.png);" ;
    QString _comphoto=":/image/"+com->get_name()+".png";
    QPixmap  myphoto=QPixmap(_myphoto);
    QPixmap  comphoto=QPixmap(_comphoto);
    ui->myphoto->setStyleSheet(_myphoto);
    ui->comphoto->setPixmap(comphoto);  // qDebug()<<"aa";
    QString myname=my->get_name();
    QString comname=com->get_name();
    ui->myname->setText(myname);
    ui->comname->setText(comname);
    //开始战斗
    QString battle1,battle2;//battle1,2分别表示战斗过程的提示语句
    int myTime=my->get_attack_interval();
    int comTime=com->get_attack_interval();
    QTest::qWait(interval);
    battle1="  Start Battle !";
    battle2="  "+myname+" vs "+comname+" !";
    ui->battle1->setText(battle1);
    ui->battle2->setText(battle2);
    int first=myTime,second=comTime;
    bool isCurrent=false;
    int myCrit,comCrit;
    int myAvoid,comAvoid;
    int n;
    QString mySkill,comSkill,comskill;
    int myhurt,comhurt;
    if(first==second)
    {
        isCurrent=true;//同时出招
    }


    while(1)
     {
        qDebug()<<QString::number(comhurt);
        myCrit=qrand()%100;
        comCrit=qrand()%100;
        myAvoid=qrand()%100;
        comAvoid=qrand()%100;
        if(isCurrent)//同时出招
        {
            n=qrand()%2;
            if(n==0)//我方进攻
            {

                //your turn
                //QTest::qWait(interval);
                my->toAttack(mySkill,myhurt);
                if(comAvoid<avoidrate)//
                {
                    battle1="  your "+myname+" use "+mySkill;
                    battle2="  but "+comname+" avoid your attack";
                    ui->battle1->setText(battle1);
                    ui->battle2->setText(battle2);
                    moveMy();
                }
                else
                {
                    myhurt-=com->get_defense();//减去对方的防御
                    if(myhurt<0)
                        myhurt=1;
                    if(myCrit<critrate)
                    {
                        battle1="  your "+myname+" use "+mySkill;
                        battle2="  make a deadly hit!";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);


                        com_hp-=myhurt*2;
                        if(com_hp<=0)com_hp=0;
                        //ui->comHP->setValue(com_hp);
                        moveMy();moveCom();
                        comHpAnimation->setDuration(hpAnimation);
                        comHpAnimation->setStartValue(ui->comHP->value());
                        comHpAnimation->setEndValue(com_hp);
                        comHpAnimation->start();
                        QTest::qWait(hpAnimation);


                        battle1="  "+comname+" get "+QString::number(myhurt*2)+" damage!";
                        battle2="  ";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        if(com_hp<=0)
                        {
                            QTest::qWait(interval);
                            battle1="  Congratulation!";
                            battle2="  your "+myname+" win "+"the game!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            comDie();
                            emit win(1);
                            break;
                        }
                    }
                    else
                    {
                        battle1="  your "+myname+" use "+mySkill;
                        battle2="  "+comname+" get "+QString::number(myhurt)+" damage!";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        com_hp-=myhurt;
                        if(com_hp<=0)com_hp=0;
                        //ui->comHP->setValue(com_hp);
                        moveMy();moveCom();
                        comHpAnimation->setDuration(hpAnimation);
                        comHpAnimation->setStartValue(ui->comHP->value());
                        comHpAnimation->setEndValue(com_hp);
                        comHpAnimation->start();
                        QTest::qWait(hpAnimation);

                        if(com_hp<=0)
                        {
                            QTest::qWait(interval);
                            battle1="  Congratulation!";
                            battle2="  your "+myname+" win "+"the game!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            comDie();
                            emit win(1);
                            break;
                        }
                    }
                }

                //com turn

                QTest::qWait(interval);
                com->toAttack(comSkill,comhurt);
                if(myAvoid<avoidrate)//
                {
                    battle1="  enemy's "+comname+" use "+comSkill;
                    battle2="  so nice! your "+myname+" avoid its attack!";
                    ui->battle1->setText(battle1);
                    ui->battle2->setText(battle2);
                    moveCom();
                }
                else
                {
                    comhurt-=my->get_defense();//减去对方的防御
                    if(comhurt<0)
                        comhurt=1;
                    if(comCrit<critrate)
                    {
                        battle1="  enemy's "+comname+" use "+comSkill;
                        battle2="  make a deadly hit!";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        QTest::qWait(1000);
                        battle1="  your "+myname+" get "+QString::number(comhurt*2)+" damage!";
                        battle2="  ";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        moveCom();
                        moveMy();

                        my_hp-=comhurt*2;
                        if(my_hp<=0)my_hp=0;
                        //ui->myHP->setValue(my_hp);
                        myHpAnimation->setDuration(hpAnimation);
                        myHpAnimation->setStartValue(ui->myHP->value());
                        myHpAnimation->setEndValue(my_hp);
                        myHpAnimation->start();
                        QTest::qWait(hpAnimation);

                        if(my_hp<=0)
                        {
                            QTest::qWait(interval);
                            battle1="  So Sad";
                            battle2="  your "+myname+" lose "+"the game!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            meDie();
                            emit win(0);
                            break;
                        }
                    }
                    else
                    {
                        battle1="  enemy's "+comname+" use "+comSkill;
                        battle2="  your "+myname+" get "+QString::number(comhurt)+" damage!";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        moveCom();moveMy();
                        my_hp-=myhurt;
                        if(my_hp<=0)my_hp=0;
                        //ui->myHP->setValue(my_hp);
                        myHpAnimation->setDuration(hpAnimation);
                        myHpAnimation->setStartValue(ui->myHP->value());
                        myHpAnimation->setEndValue(my_hp);
                        myHpAnimation->start();
                        QTest::qWait(hpAnimation);


                        if(my_hp<=0)
                        {
                            QTest::qWait(interval);
                            battle1="  So Sad!";
                            battle2="  your "+myname+" lose "+"the game!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            meDie();
                            emit win(0);
                            break;
                        }
                    }
                }//
            }
            else //com first
            {
                //com turn
                QTest::qWait(interval);
                com->toAttack(comSkill,comhurt);
                if(myAvoid<avoidrate)//
                {
                    battle1="  enemy's "+comname+" use "+comSkill;
                    battle2="  so nice! your "+myname+" avoid its attack!";
                    ui->battle1->setText(battle1);
                    ui->battle2->setText(battle2);
                    moveCom();
                }
                else
                {
                    comhurt-=my->get_defense();//减去对方的防御
                    if(comhurt<0)
                        comhurt=1;
                    if(comCrit<critrate)
                    {
                        battle1="  enemy's "+comname+" use "+comSkill;
                        battle2="  make a deadly hit!";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        QTest::qWait(1000);
                        battle1="  your "+myname+" get "+QString::number(comhurt*2)+" damage!";
                        battle2="  ";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        moveCom();
                        my_hp-=comhurt*2;
                        if(my_hp<=0)my_hp=0;
                        moveMy();
                        myHpAnimation->setDuration(hpAnimation);
                        myHpAnimation->setStartValue(ui->myHP->value());
                        myHpAnimation->setEndValue(my_hp);
                        myHpAnimation->start();
                        QTest::qWait(hpAnimation);

                        if(my_hp<=0)
                        {
                            QTest::qWait(interval);
                            battle1="  So Sad";
                            battle2="  your "+myname+" lose "+"the game!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            meDie();
                            emit win(0);
                            break;
                        }
                    }
                    else
                    {
                        battle1="  enemy's "+comname+" use "+comSkill;
                        battle2="  your "+myname+" get "+QString::number(comhurt)+" damage!";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        moveCom();
                        my_hp-=myhurt;
                        if(my_hp<=0)my_hp=0;
                        moveMy();
                        myHpAnimation->setDuration(hpAnimation);
                        myHpAnimation->setStartValue(ui->myHP->value());
                        myHpAnimation->setEndValue(my_hp);
                        myHpAnimation->start();
                        QTest::qWait(hpAnimation);

                        if(my_hp<=0)
                        {
                            QTest::qWait(interval);
                            battle1="  So Sad!";
                            battle2="  your "+myname+" lose "+"the game!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            meDie();
                            emit win(0);
                            break;
                        }
                    }
                }
                //my turn
                QTest::qWait(interval);
                my->toAttack(mySkill,myhurt);
                if(comAvoid<avoidrate)//
                {
                    battle1="  your "+myname+" use "+mySkill;
                    battle2="  but "+comname+" avoid your attack";
                    ui->battle1->setText(battle1);
                    ui->battle2->setText(battle2);
                    moveMy();
                }
                else
                {
                    myhurt-=com->get_defense();//减去对方的防御
                    if(myhurt<0)
                        myhurt=1;
                    if(myCrit<critrate)
                    {
                        battle1="  your "+myname+" use "+mySkill;
                        battle2="  make a deadly hit!";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        QTest::qWait(1000);
                        battle1="  "+comname+" get "+QString::number(myhurt*2)+" damage!";
                        battle2="  ";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        moveMy();

                        com_hp-=myhurt*2;
                        if(com_hp<=0)com_hp=0;
                        moveCom();
                        comHpAnimation->setDuration(hpAnimation);
                        comHpAnimation->setStartValue(ui->comHP->value());
                        comHpAnimation->setEndValue(com_hp);
                        comHpAnimation->start();
                        QTest::qWait(hpAnimation);

                        if(com_hp<=0)
                        {
                            QTest::qWait(interval);
                            battle1="  Congratulation!";
                            battle2="  your "+myname+" win "+"the game!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            comDie();
                            emit win(1);
                            break;
                        }
                    }
                    else
                    {
                        battle1="  your "+myname+" use "+mySkill;
                        battle2="  "+comname+" get "+QString::number(myhurt)+" damage!";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        moveMy();

                        com_hp-=myhurt;
                        if(com_hp<=0)com_hp=0;
                        moveCom();
                        comHpAnimation->setDuration(hpAnimation);
                        comHpAnimation->setStartValue(ui->comHP->value());
                        comHpAnimation->setEndValue(com_hp);
                        comHpAnimation->start();
                        QTest::qWait(hpAnimation);

                        if(com_hp<=0)
                        {
                            QTest::qWait(interval);
                            battle1="  Congratulation!";
                            battle2="  your "+myname+" win "+"the game!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            comDie();
                            emit win(1);
                            break;
                        }
                    }
                }
            }
        }



        else
        {
            first--;second--;
            if(first==-1&&second==-1)
            {
                n=qrand()%2;
                if(n==0)//我方先进攻
                {
                    //my
                    first=myTime;
                    my->toAttack(mySkill,myhurt);
                    if(comAvoid<avoidrate)//
                    {
                        battle1="  your "+myname+" use "+mySkill;
                        battle2="  but "+comname+" avoid your attack";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        moveMy();
                    }
                    else
                    {
                        myhurt-=com->get_defense();//减去对方的防御
                        if(myhurt<0)
                            myhurt=1;
                        if(myCrit<critrate)
                        {
                            battle1="  your "+myname+" use "+mySkill;
                            battle2="  make a deadly hit!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);


                            com_hp-=myhurt*2;
                            if(com_hp<=0)com_hp=0;
                            //ui->comHP->setValue(com_hp);
                            moveMy();moveCom();
                            comHpAnimation->setDuration(hpAnimation);
                            comHpAnimation->setStartValue(ui->comHP->value());
                            comHpAnimation->setEndValue(com_hp);
                            comHpAnimation->start();
                            QTest::qWait(hpAnimation);


                            battle1="  "+comname+" get "+QString::number(myhurt*2)+" damage!";
                            battle2="  ";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            if(com_hp<=0)
                            {
                                QTest::qWait(interval);
                                battle1="  Congratulation!";
                                battle2="  your "+myname+" win "+"the game!";
                                ui->battle1->setText(battle1);
                                ui->battle2->setText(battle2);
                                comDie();
                                emit win(1);
                                break;
                            }
                        }
                        else
                        {
                            battle1="  your "+myname+" use "+mySkill;
                            battle2="  "+comname+" get "+QString::number(myhurt)+" damage!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            com_hp-=myhurt;
                            if(com_hp<=0)com_hp=0;
                            //ui->comHP->setValue(com_hp);
                            moveMy();moveCom();
                            comHpAnimation->setDuration(hpAnimation);
                            comHpAnimation->setStartValue(ui->comHP->value());
                            comHpAnimation->setEndValue(com_hp);
                            comHpAnimation->start();
                            QTest::qWait(hpAnimation);

                            if(com_hp<=0)
                            {
                                QTest::qWait(interval);
                                battle1="  Congratulation!";
                                battle2="  your "+myname+" win "+"the game!";
                                ui->battle1->setText(battle1);
                                ui->battle2->setText(battle2);
                                comDie();
                                emit win(1);
                                break;
                            }
                        }
                    }

                    //com turn
                    second=comTime;
                    QTest::qWait(interval);
                    com->toAttack(comSkill,comhurt);
                    if(myAvoid<avoidrate)//
                    {
                        battle1="  enemy's "+comname+" use "+comSkill;
                        battle2="  so nice! your "+myname+" avoid its attack!";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        moveCom();
                    }
                    else
                    {
                        comhurt-=my->get_defense();//减去对方的防御
                        if(comhurt<0)
                            comhurt=1;
                        if(comCrit<critrate)
                        {
                            battle1="  enemy's "+comname+" use "+comSkill;
                            battle2="  make a deadly hit!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            QTest::qWait(1000);
                            battle1="  your "+myname+" get "+QString::number(comhurt*2)+" damage!";
                            battle2="  ";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            moveCom();
                            moveMy();

                            my_hp-=comhurt*2;
                            if(my_hp<=0)my_hp=0;
                            //ui->myHP->setValue(my_hp);
                            myHpAnimation->setDuration(hpAnimation);
                            myHpAnimation->setStartValue(ui->myHP->value());
                            myHpAnimation->setEndValue(my_hp);
                            myHpAnimation->start();
                            QTest::qWait(hpAnimation);

                            if(my_hp<=0)
                            {
                                QTest::qWait(interval);
                                battle1="  So Sad";
                                battle2="  your "+myname+" lose "+"the game!";
                                ui->battle1->setText(battle1);
                                ui->battle2->setText(battle2);
                                meDie();
                                emit win(0);
                                break;
                            }
                        }
                        else
                        {
                            battle1="  enemy's "+comname+" use "+comSkill;
                            battle2="  your "+myname+" get "+QString::number(comhurt)+" damage!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            moveCom();moveMy();
                            my_hp-=myhurt;
                            if(my_hp<=0)my_hp=0;
                            //ui->myHP->setValue(my_hp);
                            myHpAnimation->setDuration(hpAnimation);
                            myHpAnimation->setStartValue(ui->myHP->value());
                            myHpAnimation->setEndValue(my_hp);
                            myHpAnimation->start();
                            QTest::qWait(hpAnimation);


                            if(my_hp<=0)
                            {
                                QTest::qWait(interval);
                                battle1="  So Sad!";
                                battle2="  your "+myname+" lose "+"the game!";
                                ui->battle1->setText(battle1);
                                ui->battle2->setText(battle2);
                                meDie();
                                emit win(0);
                                break;
                            }
                        }
                    }//


                }
                else //电脑先进攻
                {
                    //com
                    second=comTime;
                    com->toAttack(comSkill,comhurt);
                    if(myAvoid<avoidrate)//
                    {
                        battle1="  enemy's "+comname+" use "+comSkill;
                        battle2="  so nice! your "+myname+" avoid its attack!";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        moveCom();
                    }
                    else
                    {
                        comhurt-=my->get_defense();//减去对方的防御
                        if(comhurt<0)
                            comhurt=1;
                        if(comCrit<critrate)
                        {
                            battle1="  enemy's "+comname+" use "+comSkill;
                            battle2="  make a deadly hit!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            QTest::qWait(1000);
                            battle1="  your "+myname+" get "+QString::number(comhurt*2)+" damage!";
                            battle2="  ";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            moveCom();
                            moveMy();

                            my_hp-=comhurt*2;
                            if(my_hp<=0)my_hp=0;
                            //ui->myHP->setValue(my_hp);
                            myHpAnimation->setDuration(hpAnimation);
                            myHpAnimation->setStartValue(ui->myHP->value());
                            myHpAnimation->setEndValue(my_hp);
                            myHpAnimation->start();
                            QTest::qWait(hpAnimation);

                            if(my_hp<=0)
                            {
                                QTest::qWait(interval);
                                battle1="  So Sad";
                                battle2="  your "+myname+" lose "+"the game!";
                                ui->battle1->setText(battle1);
                                ui->battle2->setText(battle2);
                                meDie();
                                emit win(0);
                                break;
                            }
                        }
                        else
                        {
                            battle1="  enemy's "+comname+" use "+comSkill;
                            battle2="  your "+myname+" get "+QString::number(comhurt)+" damage!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            moveCom();moveMy();
                            my_hp-=myhurt;
                            if(my_hp<=0)my_hp=0;
                            //ui->myHP->setValue(my_hp);
                            myHpAnimation->setDuration(hpAnimation);
                            myHpAnimation->setStartValue(ui->myHP->value());
                            myHpAnimation->setEndValue(my_hp);
                            myHpAnimation->start();
                            QTest::qWait(hpAnimation);


                            if(my_hp<=0)
                            {
                                QTest::qWait(interval);
                                battle1="  So Sad!";
                                battle2="  your "+myname+" lose "+"the game!";
                                ui->battle1->setText(battle1);
                                ui->battle2->setText(battle2);
                                meDie();
                                emit win(0);
                                break;
                            }
                        }
                    }//
                    //my
                    //com
                    QTest::qWait(interval);
                    //my
                    first=myTime;
                    my->toAttack(mySkill,myhurt);
                    if(comAvoid<avoidrate)//
                    {
                        battle1="  your "+myname+" use "+mySkill;
                        battle2="  but "+comname+" avoid your attack";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        moveMy();
                    }
                    else
                    {
                        myhurt-=com->get_defense();//减去对方的防御
                        if(myhurt<0)
                            myhurt=1;
                        if(myCrit<critrate)
                        {
                            battle1="  your "+myname+" use "+mySkill;
                            battle2="  make a deadly hit!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);


                            com_hp-=myhurt*2;
                            if(com_hp<=0)com_hp=0;
                            //ui->comHP->setValue(com_hp);
                            moveMy();moveCom();
                            comHpAnimation->setDuration(hpAnimation);
                            comHpAnimation->setStartValue(ui->comHP->value());
                            comHpAnimation->setEndValue(com_hp);
                            comHpAnimation->start();
                            QTest::qWait(hpAnimation);


                            battle1="  "+comname+" get "+QString::number(myhurt*2)+" damage!";
                            battle2="  ";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            if(com_hp<=0)
                            {
                                QTest::qWait(interval);
                                battle1="  Congratulation!";
                                battle2="  your "+myname+" win "+"the game!";
                                ui->battle1->setText(battle1);
                                ui->battle2->setText(battle2);
                                comDie();
                                emit win(1);
                                break;
                            }
                        }
                        else
                        {
                            battle1="  your "+myname+" use "+mySkill;
                            battle2="  "+comname+" get "+QString::number(myhurt)+" damage!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            com_hp-=myhurt;
                            if(com_hp<=0)com_hp=0;
                            //ui->comHP->setValue(com_hp);
                            moveMy();moveCom();
                            comHpAnimation->setDuration(hpAnimation);
                            comHpAnimation->setStartValue(ui->comHP->value());
                            comHpAnimation->setEndValue(com_hp);
                            comHpAnimation->start();
                            QTest::qWait(hpAnimation);

                            if(com_hp<=0)
                            {
                                QTest::qWait(interval);
                                battle1="  Congratulation!";
                                battle2="  your "+myname+" win "+"the game!";
                                ui->battle1->setText(battle1);
                                ui->battle2->setText(battle2);
                                comDie();
                                emit win(1);
                                break;
                            }
                        }
                    }

                }

            }
            else if(first==-1)//我方进攻
            {
                QTest::qWait(interval);
                first=myTime;
                my->toAttack(mySkill,myhurt);
                if(comAvoid<avoidrate)//
                {
                    battle1="  your "+myname+" use "+mySkill;
                    battle2="  but "+comname+" avoid your attack";
                    ui->battle1->setText(battle1);
                    ui->battle2->setText(battle2);
                    moveMy();
                }
                else
                {
                    myhurt-=com->get_defense();//减去对方的防御
                    if(myhurt<0)
                        myhurt=1;
                    if(myCrit<critrate)
                    {
                        battle1="  your "+myname+" use "+mySkill;
                        battle2="  make a deadly hit!";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);


                        com_hp-=myhurt*2;
                        if(com_hp<=0)com_hp=0;
                        //ui->comHP->setValue(com_hp);
                        moveMy();moveCom();
                        comHpAnimation->setDuration(hpAnimation);
                        comHpAnimation->setStartValue(ui->comHP->value());
                        comHpAnimation->setEndValue(com_hp);
                        comHpAnimation->start();
                        QTest::qWait(hpAnimation);


                        battle1="  "+comname+" get "+QString::number(myhurt*2)+" damage!";
                        battle2="  ";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        if(com_hp<=0)
                        {
                            QTest::qWait(interval);
                            battle1="  Congratulation!";
                            battle2="  your "+myname+" win "+"the game!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            comDie();
                            emit win(1);
                            break;
                        }
                    }
                    else
                    {
                        battle1="  your "+myname+" use "+mySkill;
                        battle2="  "+comname+" get "+QString::number(myhurt)+" damage!";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        com_hp-=myhurt;
                        if(com_hp<=0)com_hp=0;
                        //ui->comHP->setValue(com_hp);
                        moveMy();moveCom();
                        comHpAnimation->setDuration(hpAnimation);
                        comHpAnimation->setStartValue(ui->comHP->value());
                        comHpAnimation->setEndValue(com_hp);
                        comHpAnimation->start();
                        QTest::qWait(hpAnimation);

                        if(com_hp<=0)
                        {
                            QTest::qWait(interval);
                            battle1="  Congratulation!";
                            battle2="  your "+myname+" win "+"the game!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            comDie();
                            emit win(1);
                            break;
                        }
                    }
                }

            }
            else if(second==-1)
            {
                second=comTime;
                QTest::qWait(interval);
                com->toAttack(comSkill,comhurt);
                if(myAvoid<avoidrate)//
                {
                    battle1="  enemy's "+comname+" use "+comSkill;
                    battle2="  so nice! your "+myname+" avoid its attack!";
                    ui->battle1->setText(battle1);
                    ui->battle2->setText(battle2);
                    moveCom();
                }
                else
                {
                    comhurt-=my->get_defense();//减去对方的防御
                    if(comhurt<0)
                        comhurt=1;
                    if(comCrit<critrate)
                    {
                        battle1="  enemy's "+comname+" use "+comSkill;
                        battle2="  make a deadly hit!";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        QTest::qWait(1000);
                        battle1="  your "+myname+" get "+QString::number(comhurt*2)+" damage!";
                        battle2="  ";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        moveCom();
                        my_hp-=comhurt*2;
                        if(my_hp<=0)my_hp=0;
                        moveMy();
                        myHpAnimation->setDuration(hpAnimation);
                        myHpAnimation->setStartValue(ui->myHP->value());
                        myHpAnimation->setEndValue(my_hp);
                        myHpAnimation->start();
                        QTest::qWait(hpAnimation);

                        if(my_hp<=0)
                        {
                            QTest::qWait(interval);
                            battle1="  So Sad";
                            battle2="  your "+myname+" lose "+"the game!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            meDie();
                            emit win(0);
                            break;
                        }
                    }
                    else
                    {
                        battle1="  enemy's "+comname+" use "+comSkill;
                        battle2="  your "+myname+" get "+QString::number(comhurt)+" damage!";
                        ui->battle1->setText(battle1);
                        ui->battle2->setText(battle2);
                        moveCom();
                        my_hp-=myhurt;
                        if(my_hp<=0)my_hp=0;
                        moveMy();
                        myHpAnimation->setDuration(hpAnimation);
                        myHpAnimation->setStartValue(ui->myHP->value());
                        myHpAnimation->setEndValue(my_hp);
                        myHpAnimation->start();
                        QTest::qWait(hpAnimation);

                        if(my_hp<=0)
                        {
                            QTest::qWait(interval);
                            battle1="  So Sad!";
                            battle2="  your "+myname+" lose "+"the game!";
                            ui->battle1->setText(battle1);
                            ui->battle2->setText(battle2);
                            meDie();
                            emit win(0);
                            break;
                        }
                    }
                }
            }
        }
        //ui->war->scrollToBottom();

     }
    //返回战斗结果


}





/*void Fight::createMyPoke(QString name, QString _style, int level,
                          QString _power, QString _hp, QString _defense, QString _agile)
{
    Poke_quality style=stringToPokeQuality[_style];
    Quality power=stringToQuality[_power];
    Quality hp=stringToQuality[_hp];
    Quality defense=stringToQuality[_defense];
    Quality agile=stringToQuality[_agile];
    //Bulbasaur Charmander Kingler Lapras Muk Pidgeotto Pikachu Primeape Snorlax Squirtle Tauros
    if(name=="Bulbasaur")
    {
        mypoke=new Bulbasaur(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Charmander")
    {
        mypoke=new Charmander(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Kingler")
    {
        mypoke=new Kingler(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Lapras")
    {
        mypoke=new Lapras(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Muk")
    {
        mypoke=new Muk(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Pidgeotto")
    {
        mypoke=new Pidgeotto(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Pikachu")
    {
        mypoke=new Pikachu(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Primeape")
    {
        mypoke=new Primeape(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Snorlax")
    {
        mypoke=new Snorlax(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Squirtle")
    {
        mypoke=new Squirtle(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Tauros")
    {
        mypoke=new Tauros(level,0,style,power,hp,defense,agile);
        return;
    }
}

void Fight::createComPoke(QString name, QString _style, int level, QString _power, QString _hp, QString _defense, QString _agile)
{
    Poke_quality style=stringToPokeQuality[_style];
    Quality power=stringToQuality[_power];
    Quality hp=stringToQuality[_hp];
    Quality defense=stringToQuality[_defense];
    Quality agile=stringToQuality[_agile];
    //Bulbasaur Charmander Kingler Lapras Muk Pidgeotto Pikachu Primeape Snorlax Squirtle Tauros
    if(name=="Bulbasaur")
    {
        compoke=new Bulbasaur(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Charmander")
    {
        compoke=new Charmander(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Kingler")
    {
        compoke=new Kingler(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Lapras")
    {
        compoke=new Lapras(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Muk")
    {
        compoke=new Muk(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Pidgeotto")
    {
        compoke=new Pidgeotto(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Pikachu")
    {
        compoke=new Pikachu(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Primeape")
    {
        compoke=new Primeape(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Snorlax")
    {
        compoke=new Snorlax(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Squirtle")
    {
        compoke=new Squirtle(level,0,style,power,hp,defense,agile);
        return;
    }
    else if(name=="Tauros")
    {
        compoke=new Tauros(level,0,style,power,hp,defense,agile);
        return;
    }
}
*/

void Fight::moveMy()//实现移动我方的动画
{
    myMoveAnimation->setDuration(500);
    int x=ui->myphoto->geometry().x();
    int y=ui->myphoto->geometry().y();
    int width=ui->myphoto->geometry().width();
    int height=ui->myphoto->geometry().height();
    myMoveAnimation->setEndValue(QRectF(x+20,y,width,height));
    myMoveAnimation->start();
    QTest::qWait(600);
    myMoveAnimation->setDuration(500);
    myMoveAnimation->setEndValue(QRectF(x-20,y,width,height));
    myMoveAnimation->start();
    QTest::qWait(600);
    myMoveAnimation->setDuration(500);
    myMoveAnimation->setEndValue(QRectF(x,y,width,height));
    myMoveAnimation->start();
    QTest::qWait(600);

}

void Fight::moveCom()//实现移动电脑的动画
{
    comMoveAnimation->setDuration(500);
    int x=ui->comphoto->geometry().x();
    int y=ui->comphoto->geometry().y();
    int width=ui->comphoto->geometry().width();
    int height=ui->comphoto->geometry().height();
    comMoveAnimation->setEndValue(QRectF(x+20,y,width,height));
    comMoveAnimation->start();
    QTest::qWait(600);
    comMoveAnimation->setDuration(500);
    comMoveAnimation->setEndValue(QRectF(x-20,y,width,height));
    comMoveAnimation->start();
    QTest::qWait(600);
    comMoveAnimation->setDuration(500);
    comMoveAnimation->setEndValue(QRectF(x,y,width,height));
    comMoveAnimation->start();
    QTest::qWait(600);
}

void Fight::meDie()//我方死亡动画
{
    myDieAninmation->setDuration(2222);
    int x=ui->myphoto->geometry().x();
    int y=ui->myphoto->geometry().y();
    int width=ui->myphoto->geometry().width();
    int height=ui->myphoto->geometry().height();
    myDieAninmation->setEndValue(QRectF(x,y+200,width,height));
    myDieAninmation->start();
    QTest::qWait(2222);
}

void Fight::comDie()//电脑死亡动画
{
    comDieAnimation->setDuration(2222);
    int x=ui->comphoto->geometry().x();
    int y=ui->comphoto->geometry().y();
    int width=ui->comphoto->geometry().width();
    int height=ui->comphoto->geometry().height();
    comDieAnimation->setEndValue(QRectF(x,y+200,width,height));
    comDieAnimation->start();
    QTest::qWait(2222);
}

void Fight::on_start_clicked()//开始战斗按钮
{
    ui->start->setEnabled(false);
    fighting(mypoke,compoke);
}

void Fight::result(bool win)
{
    // _type 0升级 1决斗赛
    if(win)//胜利
    {
        if(_type)//决斗赛胜利
        {
            ui->battle1->setText("you get that poke!!");
            ui->battle2->setText("it belong to you now!");
            theShare::userPoke.append(compoke);
            mypoke->add_exp(10);
            theShare::myInfo.win1++;
        }
        else//升级赛胜利
        {
            ui->battle1->setText("you win it");
            ui->battle2->setText("get 10 exp");
            mypoke->add_exp(10);
            theShare::myInfo.win++;
        }
    }
    else
    {
        if(_type)//决斗赛失败
        {
            theShare::userPoke.removeOne(mypoke);
            ui->battle1->setText("you lose your pokemon");
            ui->battle2->setText("you can pay 100 for it");
            theShare::myInfo.lose1++;
        }
        else//升级赛失败
        {
            ui->battle1->setText("just a level-up game");
            ui->battle2->setText("no punish!");
            theShare::myInfo.lose++;
        }
    }
     Widget::returnMyInformation();//向服务器返回用户信息
     QTest::qWait(2000);
    Widget::returnMyPoke();//向服务器返回用户的精灵
     QTest::qWait(2000);
    emit gg();
    this->deleteLater();

}
