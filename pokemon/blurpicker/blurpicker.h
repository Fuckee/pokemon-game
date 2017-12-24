#ifndef BLURPICKER_H
#define BLURPICKER_H
#include <QGraphicsEffect>
#include <QGraphicsView>
#include <QPropertyAnimation>
#include"blurpicker/friendview.h"
#include"theshare.h"
#include "blureffect.h"
#include"friendview.h"
#include"twochoose.h"
#include"theshare.h"
#include"fightchose.h"
class BlurPicker: public QGraphicsView//选择功能界面
{
    Q_OBJECT
    Q_PROPERTY(qreal index READ index WRITE setIndex)

public:
    BlurPicker(QWidget *parent = 0);

    qreal index() const;
    void setIndex(qreal);

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    void setupScene();
    int now_chose;
private slots:
    void isClicked();
    void enterFriend();
    void enterMy();
    void enterFight();

private:
    qreal m_index;
    QGraphicsTextItem* text;
    QList<QGraphicsItem*> m_icons;
    QPropertyAnimation m_animation;
};

#endif // BLURPICKER_H
