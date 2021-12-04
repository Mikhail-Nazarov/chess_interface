#include "queen.h"
#include "game.h"
extern Game *game;
Queen::Queen(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setImage();
}

void Queen::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/images/queen1.png"));
    else
        setPixmap(QPixmap(":/images/queen.png"));
}


