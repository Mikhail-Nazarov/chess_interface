#include "rook.h"
#include "game.h"

extern Game *game;
Rook::Rook(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setImage();
}


void Rook::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/images/rook1.png"));
    else
        setPixmap(QPixmap(":/images/rook.png"));
}



