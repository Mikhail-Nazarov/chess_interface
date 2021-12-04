
#include <QApplication>
#include "game.h"
#include "chessboard.h"

Game *game;
ChessBoard *chess;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->show();
    game->displayMainMenu();
    return a.exec();
}
