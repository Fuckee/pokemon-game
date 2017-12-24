#ifndef BUTTON_H
#define BUTTON_H
#include <QtWidgets>
#include <QtCore/qmath.h>
class Button : public QGraphicsWidget
{
    Q_OBJECT
public:
    Button(const QPixmap &pixmap,const QPixmap &pixmap2, QGraphicsItem *parent = 0)
        : QGraphicsWidget(parent), _pix(pixmap),_pix2(pixmap2)
    {

        setCacheMode(ItemCoordinateCache);

        setAcceptHoverEvents(true);
        isin=false;
        isSelect=false;
    }

    QRectF boundingRect() const Q_DECL_OVERRIDE
    {
        int width=_pix.width();
        int height=_pix.height();
        return QRectF(-width/2,-height/2,width,height);
    }

    QPainterPath shape() const Q_DECL_OVERRIDE
    {
        QPainterPath path;
        path.addEllipse(boundingRect());
        return path;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) Q_DECL_OVERRIDE
    {
        bool down = option->state & QStyle::State_Sunken;
        if(down)
        {
        }
        if(isin&&!down)
        {
            painter->drawPixmap(-_pix.width()/2, -_pix.height()/2, _pix2);
        }
        else
            painter->drawPixmap(-_pix.width()/2, -_pix.height()/2, _pix);
    }

signals:
    void pressed();


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE
    {
        emit pressed();
        update();

    }
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE
    {
        isin=true;
        update();
    }
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE
    {
        isin=false;
        update();
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE
    {
        update();

    }

private:
    QPixmap _pix,_pix2;
    bool isin;
public:
    bool isSelect;
};

#endif // BUTTON_H
