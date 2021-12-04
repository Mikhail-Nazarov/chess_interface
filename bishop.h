#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"
class Bishop:public ChessPiece
{
public:
    Bishop(QString team,QGraphicsItem *parent = 0);
    void setImage();

};


#endif // BISHOP_H
