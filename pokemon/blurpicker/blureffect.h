#ifndef BLUREFFECT_H
#define BLUREFFECT_H

#include <QGraphicsEffect>
#include <QGraphicsItem>

class BlurEffect: public QGraphicsBlurEffect//选择功能界面效果
{
public:
    BlurEffect(QGraphicsItem *item);

    void setBaseLine(qreal y) { m_baseLine = y; }

    QRectF boundingRect() const;

    void draw(QPainter *painter) Q_DECL_OVERRIDE;

private:
    void adjustForItem();

private:
    qreal m_baseLine;
    QGraphicsItem *item;
};

#endif // BLUREFFECT_H
