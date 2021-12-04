#include "king.h"
#include "game.h"
#include "pawn.h"
extern Game *game;
King::King(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setImage();
}

void King::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/images/king1.png"));
    else
        setPixmap(QPixmap(":/images/king.png"));
}


