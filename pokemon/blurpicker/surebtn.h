#ifndef SUREBTN_H
#define SUREBTN_H

#include <QtWidgets>
#include <QtCore/qmath.h>
class sureBtn : public QGraphicsWidget
{
    Q_OBJECT
public:
    sureBtn(const QPixmap &pixmap,const QPixmap &pixmap2,const int width,const int height,bool have, QGraphicsItem *parent = 0)
        : QGraphicsWidget(parent), _pix(pixmap),down_pix(pixmap2)
    {
        setAcceptHoverEvents(true);
       // setAttribute(Qt::WA_Hover,true);
        setCacheMode(DeviceCoordinateCache);
        _width=width;
        _height=height;
        _have=have;
        if(_have)
        {
            _pix=_pix.scaled(boundingRect().width()-8,boundingRect().height()-8);
            down_pix=down_pix.scaled(boundingRect().width()-10,boundingRect().height()-10);

        }
        else
        {
            _pix=_pix.scaled(boundingRect().width(),boundingRect().height());
            down_pix=down_pix.scaled(boundingRect().width(),boundingRect().height());

        }
        isin=false;
    }

    QRectF boundingRect() const Q_DECL_OVERRIDE
    {
        //return QRectF(-65, -65, 130, 130);
        return QRectF(-_width/2,-_height/2,_width,_height);
    }

    QPainterPath shape() const Q_DECL_OVERRIDE
    {
        QPainterPath path;
       // path.addEllipse(boundingRect());
        path.addEllipse(boundingRect());
        return path;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *) Q_DECL_OVERRIDE
    {
        bool down = option->state & QStyle::State_Sunken;
        /*QRectF r = boundingRect();
        QRectF r=boundingRect();
        QLinearGradient grad(r.topLeft(), r.bottomRight());
        grad.setColorAt(down ? 1 : 0, option->state & QStyle::State_MouseOver ? Qt::white : Qt::lightGray);
        grad.setColorAt(down ? 0 : 1, Qt::darkGray);
        painter->setPen(Qt::darkGray);
        painter->setBrush(grad);
        painter->drawEllipse(r);
        QLinearGradient grad2(r.topLeft(), r.bottomRight());
        grad.setColorAt(down ? 1 : 0, Qt::darkGray);
        grad.setColorAt(down ? 0 : 1, Qt::lightGray);
        painter->setPen(Qt::NoPen);
        painter->setBrush(grad);
        if (down)
            painter->translate(2, 2);*/
      //  QRectF r=boundingRect();
       // painter->drawEllipse(r.adjusted(5, 5, -5, -5));
        if(down)
        {
            QRectF r=boundingRect();
            QLinearGradient grad(r.topLeft(), r.bottomRight());
            grad.setColorAt(down ? 1 : 0, option->state & QStyle::State_MouseOver ? Qt::white : Qt::lightGray);
            grad.setColorAt(down ? 0 : 1, Qt::darkGray);
            painter->setPen(Qt::darkGray);
            painter->setBrush(grad);
        }
       // painter->drawRect(boundingRect());
        if(_have)
        {
            if(down)
            {
                painter->setBrush(Qt::darkBlue);
            }
            else
                painter->setBrush(Qt::darkRed);
            int width=boundingRect().width();
            int height=boundingRect().height();
            QRectF rect(-width/2,-height/2,width,height);
          painter->drawRect(rect);
        }

        if(isin)
        {
            painter->drawPixmap(-down_pix.width()/2, -down_pix.height()/2, down_pix);
            update();
            //qDebug()<<"down";
        }
        else
        {
            painter->drawPixmap(-_pix.width()/2, -_pix.height()/2, _pix);
            update();
        }

        //qDebug()<<_pix.width();
       /* QPen pen;  // creates a default pen

          pen.setStyle(Qt::SolidLine);
          pen.setWidth(3);
          pen.setBrush(QColor(255, 0, 0, 127));
          pen.setCapStyle(Qt::SquareCap);
          pen.setJoinStyle(Qt::RoundJoin);
        painter->setPen(pen);
        painter->drawPath(path);*/
    }

signals:
    void pressed();
    void pressed2();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *) Q_DECL_OVERRIDE
    {
        emit pressed();
        emit pressed2();
        qDebug()<<"anxiale";
        update();

    }
    void hoverEnterEvent(QGraphicsSceneHoverEvent *) Q_DECL_OVERRIDE
    {
        qDebug()<<"jinlaile";
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
    QPixmap _pix;
    QPixmap down_pix;
    bool isin;
    int _width;
    int _height;
    bool _have;
};

#endif // SUREBTN_H
