#include"blurpicker/stateitem.h"



StateItem::StateItem(const QPixmap &pix, const QPixmap &pix1,const QString &text, const QFont &font,const int width,const int height,QGraphicsItem *parent):QGraphicsWidget(parent)
{
    setAcceptHoverEvents(true);
    _pix=pix;
    _pix1=pix1;
    _text=text;
    _font=font;
    _width=width;
    _height=height;
    _pix=_pix.scaled(width,height);
    _pix1=_pix1.scaled(width,height);
    isin=false;
}

QRectF StateItem::boundingRect() const
{
     QRectF rect(-_width/2,-_height/2,_width,_height);

    return rect;
}

QPainterPath StateItem::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;

}

void StateItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    bool down = option->state & QStyle::State_Sunken;
    painter->setFont(_font);
    QPointF point(-40,10);
    if(isin)
    {
        painter->drawPixmap(boundingRect().topLeft(),_pix1);

    }
    else
    {
        painter->drawPixmap(boundingRect().topLeft(),_pix);
    }

    QPen pen(Qt::gray);
    painter->setPen(pen);
    painter->drawText(point,_text);

}

void StateItem::setText(QString text)
{
    _text=text;
}
