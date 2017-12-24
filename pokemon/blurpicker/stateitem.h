#ifndef STATEITEM_H
#define STATEITEM_H

#include <QtWidgets>
#include <QtCore/qmath.h>
#include <QGraphicsScene>
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsEffect>
#include <QGraphicsItem>

#include <math.h>
class StateItem : public QGraphicsWidget
{
    Q_OBJECT
public:
    StateItem(const QPixmap &pix,const QPixmap &pix1,const QString &text,const QFont &font,const int width,const int height, QGraphicsItem *parent = 0);
    QRectF boundingRect()const Q_DECL_OVERRIDE;
    QPainterPath shape()const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)  Q_DECL_OVERRIDE;
    void setText(QString);
private:
    QPixmap _pix;
    QPixmap _pix1;
    QString _text;
    QFont _font;
    int _width;
    int _height;
    bool isin;
signals:
    void pressed();
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) Q_DECL_OVERRIDE
    {
        isin=true;
        update();
    }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE
    {
        isin=false;
        update();
    }
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE
    {
        emit pressed();
        update();

    }


};

#endif // STATEITEM_H
