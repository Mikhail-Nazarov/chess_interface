#include "pawn.h"
#include "game.h"
#include <QDebug>
#include <typeinfo>
#include "king.h"
extern Game * game;
Pawn::Pawn(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setImage();
    firstMove = true;
}

void Pawn::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/images/pawn1.png"));
    else
        setPixmap(QPixmap(":/images/pawn.png"));
}



