#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <chessboard.h>
#include "chesspiece.h"
#include <button.h>
class Game:public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget *parent = 0);

    void drawDeadHolder(int x, int y, QColor color);
    void drawChessBoard();
    void displayDeadWhite();
    void displayDeadBlack();
    void placeInDeadPlace(ChessPiece *piece);
    void addCoords();

    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);

    ChessPiece *pieceToMove;

    QString getTurn() ;
    void setTurn( QString value);
    void changeTurn();



    ChessBox *collection[8][8];
    QGraphicsTextItem *check;
    QList <ChessPiece *> alivePiece;
    void displayMainMenu();

    void gameOver(QString value);
    void removeAll();
    void Check();
    QGraphicsTextItem movesStore;

    //список возможных ходов
    QList<QString> possibleMoves;
    //mod: +: шах, #: мат, =: пат, q,r,k,b: превращение пешки в ферзя, ладью, коня или слона
    void move(QString move);

    void setLastMove(QString);
    QString getLastMove();
public slots:
    void start();
    void restart();
private:
    Button *restartButton;
    QGraphicsScene *gameScene;
    QList <ChessPiece *> whiteDead;
    QList <ChessPiece *> blackDead;
    QGraphicsRectItem * deadHolder;
    QString turn;
    QString lastPlayerMove;
    //ChessBoard *chess;
    QList <QGraphicsItem *> listG;
    QGraphicsTextItem * turnDisplay;


};

#endif // GAME_H
