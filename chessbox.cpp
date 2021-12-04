#include "chessbox.h"
#include "game.h"
#include <QDebug>
#include "king.h"
#include <iostream>
extern Game *game;
extern ChessBoard *chess;
ChessBox::ChessBox(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    setRect(0,0,90,90);
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHasChessPiece(false);
    setChessPieceColor("NONE");
    currentPiece = NULL;
}

ChessBox::~ChessBox()
{
    delete this;
}

void ChessBox::setColor(QColor color)
{
    brush.setColor(color);
    setBrush(color);
}


void ChessBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
      //  qDebug() << getChessPieceColor();
        //Deselecting counter part of ChessPiece
        if(currentPiece == game->pieceToMove && currentPiece){

            currentPiece->mousePressEvent(event);
            return;
        }

        //if selected
        if(game->pieceToMove)
        {
            if((game->pieceToMove->moveLocation().contains(this)))
            {
                QString coord = chess->getCoord(game->pieceToMove->getCurrentBox());
                QString mod = chess->getMoveMod(game->pieceToMove->getCurrentBox(),this);
                game->pieceToMove->getCurrentBox()->resetOriginalColor();
                for(ChessBox *box:game->pieceToMove->moveLocation())
                {
                    box->resetOriginalColor();
                }
                chess->move(coord,chess->getCoord(this),mod);
                game->setLastMove(coord + "-" + chess->getCoord(this) + mod);
                game->pieceToMove=NULL;
            }
        }
        //Selecting couterpart of the chessPiece
        else if(this->getHasChessPiece())
        {
            this->currentPiece->mousePressEvent(event);
        }
}

ChessPiece* ChessBox:: getPiece()
{
    return currentPiece;
}

void ChessBox::placePiece(ChessPiece *piece)
{

    piece->setPos(x()+45- piece->pixmap().width()/2  ,y()+45-piece->pixmap().width()/2);
    piece->setCurrentBox(this);
    setHasChessPiece(true,piece);
    currentPiece = piece;
}

void ChessBox::resetOriginalColor()
{
    setColor(originalColor);
}



void ChessBox::setOriginalColor(QColor value)
{
    originalColor = value;
    setColor(originalColor);
}

bool ChessBox::getHasChessPiece()
{
    return hasChessPiece;
}

void ChessBox::setHasChessPiece(bool value, ChessPiece *piece)
{
    hasChessPiece = value;
    if(value)
        setChessPieceColor(piece->getSide());
    else
        setChessPieceColor("NONE");
}



QString ChessBox::getChessPieceColor()
{
    return chessPieceColor;
}

void ChessBox::setChessPieceColor(QString value)
{
    chessPieceColor = value;
}
