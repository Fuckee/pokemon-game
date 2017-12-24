#ifndef FRIENDVIEW_H
#define FRIENDVIEW_H
#include"information.h"
#include <QObject>
#include <QGraphicsView>
#include <QtWidgets>
#include<blurpicker/stateitem.h>
#include"surebtn.h"
#include"pokemon/bulbasaur.h"
#include"theshare.h"
#include"widget.h"
#include"pokemonbox.h"
#include"twochoose.h"
class FriendView : public QGraphicsView//好友界面
{
    Q_OBJECT
public:
    FriendView();
public slots:
    void goNext();
    void goBack();
    void deleteReturn();
    void chose1();
    void chose2();
    void chose3();
    void chose4();
    void chose(int n);
    void updateInformation();
private:
    void setupScene();
    sureBtn* nextbtn,*backbtn;
    int now_page;
    QList<QGraphicsRectItem*> rectlist;
    QList<StateItem*> statelist;
    QList<sureBtn*> pokeitemlist;
    QList<QPointF> pokemonPoints;
    void showPoke(int);
signals:
    void gg();

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
};

#endif // FRIENDVIEW_H
