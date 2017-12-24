#include"stateitem.h"
#include"surebtn.h"
#include"blurpicker/friendview.h"
#include<QTest>
FriendView::FriendView()
{
    now_page=1;
    setScene(new QGraphicsScene(this));
    scene()->setSceneRect(-300,-300,600,600);
    QPixmap bg(":/images/friend.png");
    QGraphicsPixmapItem* theBG=scene()->addPixmap(bg.scaled(680,680));
    theBG->setPos(-350,-350);
    QGraphicsRectItem* anew1=new QGraphicsRectItem;
    QPixmap nexticon(":/images/next1.png");
    QPixmap nexticon2(":/images/next2.png");
    nextbtn=new sureBtn(nexticon,nexticon2,37,53,0,anew1);
    scene()->addItem(anew1);
    connect(nextbtn,SIGNAL(pressed2()),this,SLOT(goNext()));
    nextbtn->setPos(160,-50);
    if(now_page*4>=theShare::friendlist.count())
    {
        nextbtn->setEnabled(false);
    }

    QGraphicsRectItem* anew2=new QGraphicsRectItem;
    QPixmap backicon(":/images/back1.png");
    QPixmap backicon2(":/images/back2.png");
    backbtn=new sureBtn(backicon,backicon2,37,53,0,anew2);
    scene()->addItem(anew2);
    connect(backbtn,SIGNAL(pressed2()),this,SLOT(goBack()));
    backbtn->setPos(160,-140);
    backbtn->setEnabled(false);
    backbtn->setZValue(10);
    //按钮
    QGraphicsRectItem* anew=new QGraphicsRectItem;
    QPixmap deleteicon(":/images/delete.png");
    QPixmap deleteicon2(":/images/delete2.png");
    sureBtn* btn=new sureBtn(deleteicon,deleteicon2,46,46,0,anew);
    connect(btn,SIGNAL(pressed2()),this,SLOT(deleteReturn()));
    scene()->addItem(anew);
    btn->setPos(240,-250);

    //更新在线用户按钮
    QGraphicsRectItem* anew3=new QGraphicsRectItem;
    QPixmap emptyicon;
    QPixmap emptyicon1(":/images/update1.png");
    sureBtn* updatebtn=new sureBtn(emptyicon,emptyicon1,300,80,0,anew3);
    connect(updatebtn,SIGNAL(pressed()),this,SLOT(updateInformation()));
   // connect(btn,SIGNAL(pressed2()),this,SLOT(deleteReturn()));
    scene()->addItem(anew3);
    updatebtn->setPos(-8,241);
    //精灵图片位置
    QPointF point1(-135,40);
    QPointF point2(-135,100);
    QPointF point3(-135,160);
    QPointF point4(110,40);
    QPointF point5(110,100);
    QPointF point6(110,160);
    pokemonPoints.append(point1);
    pokemonPoints.append(point4);
    pokemonPoints.append(point2);
    pokemonPoints.append(point5);
    pokemonPoints.append(point3);
    pokemonPoints.append(point6);

    setupScene();

}

void FriendView::setupScene()//60,60
{
    QFont myfont;
    myfont.setItalic(1);
    myfont.setPixelSize(34);
    QStringList name;
    name<<":/images/theline1.png";
    name<<":/images/theline3.png";
    QList<QPointF>  points;
    for(int i=0;i<4;i++)
    {
        QPointF point(-70,-165+50*i);
        points.append(point);
    }
    int up=now_page*4<=theShare::friendlist.count()?now_page*4:theShare::friendlist.count();
    for(int i=0;i<4;i++)
    {
        int index=i+1+(now_page-1)*4;
        if(index>theShare::friendlist.count())
            break;
        QGraphicsRectItem *atext=new QGraphicsRectItem;
        QString thename=theShare::friendlist.at(index-1);
        //判断是否在线
        int state=theShare::findPlayer(thename).state;
        StateItem* item;
        if(state==1)
        {
             item=new StateItem(name[0],name[0],thename,myfont,300,40,atext);
        }
        else
        {
             item=new StateItem(name[1],name[1],thename,myfont,300,40,atext);
        }
        scene()->addItem(atext);
        item->setPos(points.at(i));
        scene()->addItem(atext);
        rectlist.append(atext);
        statelist.append(item);
        switch(i)
        {
        case 0:
            connect(item,SIGNAL(pressed()),this,SLOT(chose1()));
            break;
        case 1:
            connect(item,SIGNAL(pressed()),this,SLOT(chose2()));
            break;
        case 2:
            connect(item,SIGNAL(pressed()),this,SLOT(chose3()));
            break;
        case 3:
            connect(item,SIGNAL(pressed()),this,SLOT(chose4()));
            break;
        }
    }



}

void FriendView::showPoke(int x)//index为friendlist里的序号
{
    QString name=theShare::friendlist.at(x);
    qDebug()<<"show "+name;
    int index=theShare::nameToIndex[name];
    QList< pokemon*> pokelist=theShare::OtherPoke.at(index);

    for(int i=0;i<pokelist.count();i++)
    {
        pokemon* thepoke=pokelist.at(i);
        QPointF apoint=pokemonPoints.at(i);
        QString pokename=thepoke->get_name();
        QString thePixname=":/images/"+pokename+".png";
        QPixmap thePix(thePixname);
        QGraphicsRectItem *atext=new QGraphicsRectItem;
        sureBtn* item=new sureBtn(thePix,thePix,240,50,1,atext);
        scene()->addItem(atext);
        item->setPos(apoint);
        scene()->addItem(atext);
        pokeitemlist.append(item);
    }
}

void FriendView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    qDebug()<<QPointF(event->pos().x()-300,event->pos().y()-300);

}
void FriendView::goBack()
{
     now_page--;

        setupScene();
        nextbtn->setEnabled(true);
        if(now_page==1)
        {
            backbtn->setEnabled(false);
        }
    qDebug()<<"goback";
}

void FriendView::deleteReturn()
{
    this->hide();
    emit gg();
    this->deleteLater();
}

void FriendView::chose1()
{
    qDebug()<<"chose1";
    int index=(now_page-1)*4;
    emit chose(index);
    if(pokeitemlist.count()!=0)
    {
        for(int i=0;i<pokeitemlist.count();i++)
        {
            sureBtn* aitem=pokeitemlist.at(i);
            aitem->deleteLater();
        }
        pokeitemlist.clear();
    }
    showPoke(index);
}
void FriendView::chose2()
{
    qDebug()<<"chose2";
    int index=(now_page-1)*4+1;
    emit chose(index);
    if(pokeitemlist.count()!=0)
    {
        for(int i=0;i<pokeitemlist.count();i++)
        {
            sureBtn* aitem=pokeitemlist.at(i);
            aitem->deleteLater();
        }
        pokeitemlist.clear();
    }
    showPoke(index);
}
void FriendView::chose3()
{
    qDebug()<<"chose3";
    int index=(now_page-1)*4+2;
    emit chose(index);
    if(pokeitemlist.count()!=0)
    {
        for(int i=0;i<pokeitemlist.count();i++)
        {
            sureBtn* aitem=pokeitemlist.at(i);
            aitem->deleteLater();
        }
        pokeitemlist.clear();
    }
    showPoke(index);
}
void FriendView::chose4()
{
    qDebug()<<"chose4";
    int index=(now_page-1)*4+3;
    emit chose(index);
    if(pokeitemlist.count()!=0)
    {
        for(int i=0;i<pokeitemlist.count();i++)
        {
            sureBtn* aitem=pokeitemlist.at(i);
            aitem->deleteLater();
        }
        pokeitemlist.clear();
    }
    showPoke(index);
}

void FriendView::chose(int n)
{
    QString name=theShare::friendlist.at(n);
    int index=theShare::nameToIndex[name];
    QList<pokemon*> pokelist=theShare::OtherPoke.at(index);
    player aplayer=theShare::findPlayer(name);
    TwoChoose* box=new TwoChoose(aplayer,pokelist);
    box->show();
}

void FriendView::updateInformation()
{
    Widget::askOnlineagain();
    QTest::qWait(400);
    now_page=1;
    backbtn->setEnabled(false);
    for(int i=0;i<rectlist.count();i++)
    {
        rectlist.at(i)->hide();
        statelist.at(i)->deleteLater();
    }
    rectlist.clear();
    statelist.clear();
    setupScene();
    if(now_page*4>=theShare::friendlist.count())
    {
        nextbtn->setEnabled(false);
    }
    else
        nextbtn->setEnabled(true);
}
void FriendView::goNext()
{
    now_page++;
    for(int i=0;i<rectlist.count();i++)
    {
        rectlist.at(i)->hide();
        statelist.at(i)->deleteLater();
    }
    rectlist.clear();
    statelist.clear();
    setupScene();
    backbtn->setEnabled(true);
    if(now_page*4>=theShare::friendlist.count())
    {
        nextbtn->setEnabled(false);
    }
}

