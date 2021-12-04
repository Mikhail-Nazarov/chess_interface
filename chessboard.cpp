#include "chessboard.h"
#include "chessbox.h"
#include "game.h"
#include "queen.h"
#include "rook.h"
#include "pawn.h"
#include "king.h"
#include "knight.h"
#include "bishop.h"
extern Game *game;
ChessBoard::ChessBoard()
{
    setUpBlack();
    setUpWhite();
}
void ChessBoard::drawBoxes(int x,int y)
{
    int SHIFT = 90;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            ChessBox *box = new ChessBox();
            game->collection[i][j] = box;
            box->rowLoc = i;
            box->colLoc = j;
            box->setPos(x+SHIFT*j,y+SHIFT*i);
            if((i+j)%2==0)
                box->setOriginalColor(*new QColor(191,187,161));
            else
                box->setOriginalColor(*new QColor(120,92,59));
            game->addToScene(box);
        }
    }

}

void ChessBoard::pawnTransform(ChessPiece *pawn, QString piece)
{
    ChessPiece *temp = NULL;
    if(piece == "q") temp = new Queen(pawn->getSide());
    if(piece == "r") temp = new Rook(pawn->getSide());
    if(piece == "k") temp = new Knight(pawn->getSide());
    if(piece == "b") temp = new Bishop(pawn->getSide());
    if(temp)
    {
        if(pawn->getSide()=="WHITE") white.append(temp);
        else black.append(temp);
        game->addToScene(temp);
        temp->setIsPlaced(true);
        temp->setCurrentBox(pawn->getCurrentBox());
        pawn->getCurrentBox()->placePiece(temp);
        temp->move(pawn->getCurrentBox());
        delete pawn;
    }
}

void ChessBoard::castling(QString castling)
{
    QString coord;
    if(game->getTurn()=="WHITE")
        coord='1';
    else coord = '8';
    ChessPiece *king = chooseBox("e"+coord)->getPiece();
    if(castling=="0-0")
    {
        ChessPiece *rook = chooseBox("h"+coord)->getPiece();
        if(king!=NULL && rook!=NULL)
        {
            king->move(chooseBox("g"+coord));
            rook->move(chooseBox("f"+coord));
            game->changeTurn();
        }
    }
    else
    {
        ChessPiece *rook = chooseBox("a"+coord)->getPiece();
        if(king!=NULL && rook!=NULL)
        {
            king->move(chooseBox("c"+coord));
            rook->move(chooseBox("d"+coord));
            game->changeTurn();
        }
    }
}

void ChessBoard::move(QString start, QString end, QString mod, QString _castling)
{
    ChessPiece *piece;
    ChessBox *startPos;
    ChessBox *endPos;
    if(_castling!="")
    {
        castling(_castling);
    }
    else
    {
        startPos=chooseBox(start);
        endPos=chooseBox(end);
        piece = startPos->getPiece();
        if(startPos->getHasChessPiece())
        {
            piece->move(endPos);
            game->changeTurn();
        }
    }
    if(mod!="")
    {
        if(mod=="+") game->Check();
        else if(mod=="#") game->gameOver("checkmate");
        else if(mod=="=") game->gameOver("stalemate");
        else pawnTransform(piece,mod);
    }
}


void ChessBoard::addChessPiece() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {

            ChessBox *box =game->collection[i][j];
            if(i < 2) {
                static int k;
                box->placePiece(black[k]);
                game->alivePiece.append(black[k]);
                game->addToScene(black[k++]);
            }
            if(i > 5) {
                static int h;
                box->placePiece(white[h]);
                game->alivePiece.append(white[h]);
                game->addToScene(white[h++]);
            }

        }
    }
}

void ChessBoard::setUpWhite()
{
    ChessPiece *piece;
    for(int i = 0; i < 8; i++) {
        piece = new Pawn("WHITE");
        white.append(piece);
    }
    piece = new Rook("WHITE");
    white.append(piece);
    piece = new Knight("WHITE");
    white.append(piece);
    piece = new Bishop("WHITE");
    white.append(piece);
    piece = new Queen("WHITE");
    white.append(piece);
    piece = new King("WHITE");
    white.append(piece);
    piece = new Bishop("WHITE");
    white.append(piece);
    piece = new Knight("WHITE");
    white.append(piece);
    piece = new Rook("WHITE");
    white.append(piece);

}

void ChessBoard::setUpBlack()
{
    ChessPiece *piece;
    piece = new Rook("BLACK");
    black.append(piece);
    piece = new Knight("BLACK");
    black.append(piece);
    piece = new Bishop("BLACK");
    black.append(piece);
    piece = new Queen("BLACK");
    black.append(piece);
    piece = new King("BLACK");
    black.append(piece);
    piece = new Bishop("BLACK");
    black.append(piece);
    piece = new Knight("BLACK");
    black.append(piece);
    piece = new Rook("BLACK");
    black.append(piece);
    for(int i = 0; i < 8; i++) {
        piece = new Pawn("BLACK");
        black.append(piece);
    }
}

QString ChessBoard::getCoord(ChessBox *box)
{
    for(int i = 0; i < 64;i++){
        if(game->collection[i/8][i%8]==box)
        {
            return spaces[i];
        }
    }
    return "";
}

QString ChessBoard::getMoveMod(ChessBox *start, ChessBox *end)
{
    for(auto s : game->possibleMoves)
    {
        if(s.contains(getCoord(start) + "-" + getCoord(end)))
        {
            return s.remove(getCoord(start) + "-" + getCoord(end));
        }
    }
    return "";
}

ChessBox* ChessBoard::chooseBox(QString coord)
{
    for(int i = 0; i < 64;i++){
        if(spaces[i]==coord)
        {
            return game->collection[i/8][i%8];
        }
    }
    return game->collection[0][0];
}


void ChessBoard::reset() {
    int k = 0; int h = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {

            ChessBox *box =game->collection[i][j];
            box->setHasChessPiece(false);
            box->setChessPieceColor("NONE");
            box->currentPiece = NULL;
            if(i < 2) {

                box->placePiece(black[k]);
                black[k]->setIsPlaced(true);
                black[k]->firstMove = true;
                game->alivePiece.append(black[k++]);

            }
            if(i > 5) {

                box->placePiece(white[h]);
                white[h]->setIsPlaced(true);
                white[h]->firstMove = true;
                game->alivePiece.append(white[h++]);

            }

        }
    }
}
