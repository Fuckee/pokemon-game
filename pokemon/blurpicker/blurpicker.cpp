
#include "blurpicker.h"

#include <QtWidgets>
#include <QtCore/qmath.h>
#include"button.h"
#include "blureffect.h"
#include"surebtn.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

BlurPicker::BlurPicker(QWidget *parent): QGraphicsView(parent), m_index(0.0), m_animation(this, "index")
{
    //setBackgroundBrush(QPixmap(":/images/background.jpg"));
    setScene(new QGraphicsScene(this));
    now_chose=0;
    setupScene();
    setIndex(0);
    m_animation.setDuration(400);
    m_animation.setEasingCurve(QEasingCurve::InOutSine);
    setRenderHint(QPainter::Antialiasing, true);
    setFrameStyle(QFrame::NoFrame);
    //setAttribute(Qt::WA_Hover,true);
}

qreal BlurPicker::index() const
{
    return m_index;
}

void BlurPicker::setIndex(qreal index)
{
    m_index = index;
    qreal baseline = 0;
    for (int i = 0; i < m_icons.count(); ++i) {
        QGraphicsItem *icon = m_icons[i];
        qreal a = ((i + m_index) * 2 * M_PI) / m_icons.count();
        qreal xs = 200 * qSin(a);
        qreal ys = 200 * qCos(a);
        QPointF pos(xs, ys);
        pos = QTransform().rotate(-20).map(pos);
        pos -= QPointF(40, 40);

        icon->setPos(pos);

        baseline = qMax(baseline, ys);
        static_cast<BlurEffect *>(icon->graphicsEffect())->setBaseLine(baseline);
    }

    scene()->update();
}

void BlurPicker::setupScene()
{
    QPixmap sureMap=QPixmap(":/images/sure.png");
    QPixmap sureMap2=QPixmap(":/images/down2.png");
    QGraphicsRectItem* btn=new QGraphicsRectItem(-sureMap.width()/2,-sureMap.height()/2,sureMap.width(),sureMap.height());
    sureBtn* SureBtn=new sureBtn(sureMap,sureMap2,sureMap.width(),sureMap.height(),0,btn);
    SureBtn->setPos(0,240);
    SureBtn->setZValue(6);
    scene()->addItem(SureBtn);
    //scene()->setSceneRect(-200, -120, 400, 240);
    //qDebug()<<bgg->rect().height();
    text=new QGraphicsTextItem("好友");
    text->setDefaultTextColor(QColor(50,100,200,200));
    //text->adjustSize();

    scene()->setSceneRect(-480,-270,960,540);
    QFont myfont;
    myfont.setItalic(1);
    //myfont.setFamily("宋体");
    myfont.setPixelSize(80);
    myfont.setKerning(true);
    text->setFont(myfont);
    text->setZValue(3);
    scene()->addItem(text);
    text->setPos(scene()->sceneRect().width()/2-text->boundingRect().width(),scene()->sceneRect().height()/2-text->boundingRect().height());
    /*QGraphicsRectItem* arect=new QGraphicsRectItem;
    QGraphicsWidget* widget=new QGraphicsWidget(arect);
    QGraphicsItem* item=new QGraphicsItem;
    Button* button=new Button(":/images/accessories-text-editor.png",item);
    scene()->addItem(item);*/
    QStringList names;
    names << ":/images/first1.png";
    names << ":/images/second1.png";
    names << ":/images/third1.png";
    QStringList names2;
    names2<<":/images/first2.png";
    names2<<":/images/second2.png";
    names2<<":/images/third2.png";
   // names << ":/images/internet-group-chat.png";
   // names << ":/images/internet-mail.png";
   // names << ":/images/internet-web-browser.png";
    //names << ":/images/office-calendar.png";
   // names << ":/images/system-users.png";

    for (int i = 0; i < names.count(); i++) {
        QPixmap pixmap(names[i]);
        QPixmap pixmap2(names2[i]);
        /*QGraphicsPixmapItem *icon = scene()->addPixmap(pixmap);
        icon->setZValue(1);
        icon->setGraphicsEffect(new BlurEffect(icon));
        m_icons << icon;*/
        pixmap=pixmap.scaled(100,100);
        pixmap2=pixmap2.scaled(100,100);
        QGraphicsEllipseItem* item=new QGraphicsEllipseItem;
                //=new QGraphicsEllipseItem(-wid/2,-hei/2,wid,hei);
       // QGraphicsEllipseItem* item=new QGraphicsEllipseItem(0,0,pixmap.width()/2,pixmap.height()/2);
        Button* button=new Button(pixmap,pixmap2,item);
        connect(button,SIGNAL(pressed()),this,SLOT(isClicked()));
        button->setPos(0,0);
        button->setZValue(5);
        scene()->addItem(item);
        item->setZValue(1);
        item->setGraphicsEffect(new BlurEffect(item));
        m_icons<<item;
    }
    qDebug()<<now_chose;
    for(int i=0;i<m_icons.count();i++)
    {
        if(i==now_chose)
        {
            m_icons.at(i)->setEnabled(true);
        }
        else
        {
            m_icons.at(i)->setEnabled(false);
        }
    }
    QPixmap thebg=QPixmap(":/images/bg.jpg");
    thebg=thebg.scaled(960,540);
    QGraphicsPixmapItem *bg = scene()->addPixmap(thebg);
    bg->setZValue(0);
    bg->setPos(-480, -270);
}

void BlurPicker::isClicked()
{
    switch(now_chose)
    {
    case 0:
        qDebug()<<"好友";
        enterFriend();
        break;
    case 1:
        qDebug()<<"战斗";
        enterFight();
        break;
    case 2:
        qDebug()<<"精灵";
        enterMy();
        break;
    }
}

void BlurPicker::enterFriend()
{
    this->hide();
    FriendView * friendView=new FriendView();
    friendView->setFixedSize(600,600);
    connect(friendView,SIGNAL(gg()),this,SLOT(show()));
    friendView->show();
}

void BlurPicker::enterMy()
{
    this->hide();
    TwoChoose* box=new TwoChoose(theShare::myInfo,theShare::userPoke);
    box->show();
    connect(box,SIGNAL(gg()),this,SLOT(show()));
}

void BlurPicker::enterFight()
{
    this->hide();
    FightChose* box=new FightChose(this);
    box->show();
    connect(box,SIGNAL(gg()),this,SLOT(show()));
}

void BlurPicker::keyPressEvent(QKeyEvent *event)
{
    int delta = 0;
    if(event->key()==Qt::Key_Left||event->key()==Qt::Key_Right)
    {
        switch (event->key())
        {
        case Qt::Key_Left:
            now_chose=now_chose-1;
            if(now_chose==-1)
                now_chose=2;
            delta = -1;
            break;
        case  Qt::Key_Right:
            now_chose=(now_chose+1)%3;
            delta = 1;
            break;
        default:
            break;
        }
        for(int i=0;i<m_icons.count();i++)
        {
            m_icons.at(i)->setEnabled(false);
        }
        if(now_chose==0)
            m_icons.at(0)->setEnabled(true);
        else if(now_chose==1)
            m_icons.at(2)->setEnabled(true);
        else
            m_icons.at(1)->setEnabled(true);
       // qDebug()<<now_chose;
        QFont myfont;
        myfont.setItalic(1);
        myfont.setPixelSize(80);
        switch(now_chose)
        {
        case 0://在线好友
            text->deleteLater();
            text=new QGraphicsTextItem("好友");
            text->setDefaultTextColor(QColor(50,100,200,200));
            text->setFont(myfont);
            text->setZValue(3);
            scene()->addItem(text);
            //text->setPos(-text->boundingRect().width()/2,-text->boundingRect().height()/2);
            text->setPos(scene()->sceneRect().width()/2-text->boundingRect().width(),scene()->sceneRect().height()/2-text->boundingRect().height());
            break;
        case 1://战斗
            text->deleteLater();
            text=new QGraphicsTextItem("战斗");
            text->setDefaultTextColor(QColor(50,100,50,200));
            myfont.setKerning(1);
            text->setFont(myfont);
            text->setZValue(3);
            scene()->addItem(text);
            text->setPos(scene()->sceneRect().width()/2-text->boundingRect().width(),scene()->sceneRect().height()/2-text->boundingRect().height());
            break;
        case 2://
            text->deleteLater();
            text=new QGraphicsTextItem("精灵");
            text->setDefaultTextColor(QColor(200,100,50,200));
            text->setFont(myfont);
            text->setZValue(3);
            scene()->addItem(text);
            text->setPos(scene()->sceneRect().width()/2-text->boundingRect().width(),scene()->sceneRect().height()/2-text->boundingRect().height());
            break;
        default:
            break;


        }

        if (m_animation.state() == QAbstractAnimation::Stopped && delta) {

            m_animation.setEndValue(m_index + delta);
            m_animation.start();
           // event->accept();
        }
    }

}

void BlurPicker::resizeEvent(QResizeEvent *  event )
{
    QGraphicsView::resizeEvent(event);
    fitInView(sceneRect(),Qt::KeepAspectRatio);
}



void BlurPicker::mousePressEvent(QMouseEvent *event)
{
    /*int delta = 0;
    if(event->x() > (width() / 2))
    {
        delta = 1;
    }
    else
    {
        delta = -1;
    }

    if (m_animation.state() == QAbstractAnimation::Stopped && delta) {
        m_animation.setEndValue(m_index + delta);
        m_animation.start();
       // event->accept();
    }*/
    QGraphicsView::mousePressEvent(event);
}
