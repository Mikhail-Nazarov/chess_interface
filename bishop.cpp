#include "bishop.h"
#include <QDebug>
#include "game.h"
extern Game *game;

Bishop::Bishop(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setImage();
}

void Bishop::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/images/bishop1.png"));
    else
        setPixmap(QPixmap(":/images/bishop.png"));
}

