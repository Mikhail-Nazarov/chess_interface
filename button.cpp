#include "button.h"
#include <QGraphicsTextItem>
#include <QBrush>

Button::Button(QString name, QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
{
    //draw the rect
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(*new QColor(79,55,39));
    setBrush(brush);

    //draw Text
    text = new QGraphicsTextItem(name,this);
    text->setFont(QFont("",20));
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);
    text->setDefaultTextColor(Qt::white);

    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event)
    emit clicked();

}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //change color
    if(event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(*new QColor(123,84,61));
    setBrush(brush);
    }
}
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    //change color
    if(event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(*new QColor(79,55,39));
    setBrush(brush);
    }
}
