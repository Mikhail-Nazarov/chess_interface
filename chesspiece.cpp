#include "chesspiece.h"
#include "game.h"
#include <QDebug>
#include "king.h"
#include <chessboard.h>

extern Game *game;
extern ChessBoard *chess;
ChessPiece::ChessPiece(QString team, QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    side = team;
    isPlaced = true;
    firstMove = true;
}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Deselect
    if(this == game->pieceToMove){
        game->pieceToMove->getCurrentBox()->resetOriginalColor();
        game->pieceToMove->decolor();
        game->pieceToMove = NULL;
       return;
    }
    //if it is already consumed or not the respective color's turn
    if((!getIsPlaced()) || ( (game->getTurn() != this->getSide())&& (!game->pieceToMove)) )
        return;
    //selecting
    if(!game->pieceToMove){
        game->pieceToMove = this;
        game->pieceToMove->getCurrentBox()->setColor(Qt::cyan);
        game->pieceToMove->setLocation(game->pieceToMove->getCurrentBox());
        game->pieceToMove->decolorLocation();
    }
    //Consuming counterPart of the CHessBox
    else if(this->getSide() != game->pieceToMove->getSide()){
        this->getCurrentBox()->mousePressEvent(event);
    }
}

void ChessPiece::decolorLocation()
{
    for(ChessBox *box: location)
        box->setColor(Qt:: darkCyan);
}

void ChessPiece::setLocation(ChessBox *startPos)
{
    for(auto s : game->possibleMoves)
    {
        QString temp="";
        int i=0;
        while (s[i]!='-')
        {
            temp+=s[i];
            i++;
        }
        if(startPos == chess->chooseBox(temp))
        {
            temp=s[i+1];
            temp+=s[i+2];
            location.append(chess->chooseBox(temp));
        }
    }
}

void ChessPiece::setCurrentBox(ChessBox *box)
{
    currentBox = box;
}

ChessBox *ChessPiece::getCurrentBox()
{
    return currentBox;
}

QString ChessPiece::getSide()
{
    return side;
}

void ChessPiece::setSide( QString value)
{
    side = value;
}

bool ChessPiece::getIsPlaced()
{
    return isPlaced;
}

void ChessPiece::setIsPlaced(bool value)
{
    isPlaced = value;

}
QList<ChessBox *> ChessPiece::moveLocation()
{
    return location;
}
void ChessPiece::decolor()
{
    for(size_t i = 0, n = location.size(); i < n;i++) {
         location[i]->resetOriginalColor();
    }
}

bool ChessPiece::boxSetting(ChessBox *box)
{
    if(box->getHasChessPiece()) {
        King *q = dynamic_cast<King*>(location.last()->currentPiece);
        if(q){
            box->setColor(Qt::blue);
        }
        else
            box->setColor(Qt::red);
        return true;
    }
    else
        location.last()->setColor(Qt::darkRed);
    return false;
}
void ChessPiece::move(ChessBox *endPos)
{
    ChessPiece* anotherPiece=endPos->getPiece();
    currentBox->currentPiece=NULL;
    location.clear();
    QString team = this->getSide();
    if(anotherPiece)
    {
        if(anotherPiece->getSide()==team)
            return;
        //если стоит вражеская фигура
        game->placeInDeadPlace(anotherPiece);
    }
    location.append(endPos);
    this->setCurrentBox(endPos);
    endPos->placePiece(this);
}
