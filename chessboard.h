#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include "chesspiece.h"
#include "chessbox.h"
class ChessBoard
{
public:
    ChessBoard();

    void drawBoxes(int x, int y);
    ChessBox* chooseBox(QString coord);
    QString getCoord(ChessBox *box);
    QString getMoveMod(ChessBox *start, ChessBox *end);

    void setUpWhite();
    void setUpBlack();

    void move(QString start, QString end, QString mod="", QString castling="");
    void castling(QString castling="");
    void pawnTransform(ChessPiece *pawn, QString piece);

    void addChessPiece();
    void reset();
private:
    const QString spaces[64] =
    {
        "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
        "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
        "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
        "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
        "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
        "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
        "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
        "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
    };
    QList <ChessPiece *> white;
    QList <ChessPiece *> black;



};

#endif // CHESSBOARD_H
