#include "game.h"
#include "button.h"
#include <QPixmap>
#include "king.h"
#include <QDebug>
extern ChessBoard *chess;
Game::Game(QWidget *parent ):QGraphicsView(parent)
{
    possibleMoves = {"d1-d3","c1-c3+","b1-b3","0-0","0-0-0","f8-f6","g8-g6","e2-e4", "e2-e7"};
    restartButton = new Button("Заново");
    gameScene = new QGraphicsScene();
    gameScene->setSceneRect(0,0,1400,800);

    setFixedSize(1400,800);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(gameScene);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBackgroundBrush(brush);
    pieceToMove = NULL;

    turnDisplay = new QGraphicsTextItem();
    turnDisplay->setPos(width()/2-370,10);
    turnDisplay->setZValue(1);
    turnDisplay->setDefaultTextColor(Qt::white);
    turnDisplay->setFont(QFont("",18));
    turnDisplay->setPlainText("ОЧЕРЕДЬ : WHITE");

    check = new QGraphicsTextItem();
    check->setPos(width()/2-30,10);
    check->setZValue(4);
    check->setDefaultTextColor(Qt::red);
    check->setFont(QFont("",18));
    check->setPlainText("ШАХ!");
    check->setVisible(false);
    setTurn("WHITE");
}

void Game::drawChessBoard()
{
    chess = new ChessBoard();
    drawDeadHolder(0,0,Qt::lightGray);
    drawDeadHolder(1100,0,Qt::lightGray);
    chess->drawBoxes(width()/2-360,70);
    addCoords();
}

void Game::displayDeadWhite()
{
    int SHIFT = 50;
    int j = 0;
    int k = 0;
    for(size_t i = 0,n = whiteDead.size(); i<n; i++) {
            if(j == 4){
                k++;
                j = 0;
            }
            whiteDead[i]->setPos(40+SHIFT*j++,100+SHIFT*2*k);
    }
}

void Game::addCoords()
{
    QString letters = "abcdefgh";
    int shift=90;
    QGraphicsTextItem* text;
    for(int i=0;i<8;i++)
    {
        text = new QGraphicsTextItem();
        text->setZValue(1);
        text->setDefaultTextColor(Qt::white);
        text->setFont(QFont("",10));
        text->setPlainText(letters[i]);
        text->setPos((width()/2-300)+i*shift,50);
        addToScene(text);
    }
    for(int i=0;i<8;i++)
    {
        text = new QGraphicsTextItem();
        text->setZValue(1);
        text->setDefaultTextColor(Qt::white);
        text->setFont(QFont("",10));
        text->setPlainText(QString::number(8-i));
        text->setPos(width()/2-375,(height()/2-300)+i*shift);
        addToScene(text);
    }
}

void Game::displayDeadBlack()
{
    int SHIFT = 50;
    int j = 0;
    int k = 0;
    for(size_t i = 0,n = blackDead.size(); i<n; i++) {
        if(j == 4){
            k++;
            j = 0;
        }
        blackDead[i]->setPos(1140+SHIFT*j++,100+SHIFT*2*k);
    }
}

void Game::placeInDeadPlace(ChessPiece *piece)
{
    piece->setIsPlaced(false);
    if(piece->getSide() == "БЕЛЫЕ") {
        whiteDead.append(piece);
        King *g = dynamic_cast <King *>(piece);
        displayDeadWhite();
    }
    else{
        blackDead.append(piece);
        King *g = dynamic_cast <King *>(piece);
        displayDeadBlack();
    }
    alivePiece.removeAll(piece);
}

void Game::addToScene(QGraphicsItem *item)
{
    gameScene->addItem(item);
}

void Game::removeFromScene(QGraphicsItem *item)
{
    gameScene->removeItem(item);

}

QString Game::getTurn()
{
    return turn;
}

void Game::setTurn(QString value)
{
    turn = value;
}

void Game::changeTurn()
{
    if(getTurn() == "WHITE")
        setTurn("BLACK");
    else
        setTurn("WHITE");
    turnDisplay->setPlainText("ОЧЕРЕДЬ : " + getTurn());
}

void Game::start()
{
    lastPlayerMove="";
    for(size_t i =0, n = listG.size(); i < n; i++)
        removeFromScene(listG[i]);

    addToScene(turnDisplay);
    QGraphicsTextItem* whitePiece = new QGraphicsTextItem();
    whitePiece->setPos(70,10);
    whitePiece->setZValue(1);
    whitePiece->setDefaultTextColor(Qt::black);
    whitePiece->setFont(QFont("",14));
    whitePiece->setPlainText("ФИГУРЫ БЕЛЫХ");
    addToScene(whitePiece);
    QGraphicsTextItem *blackPiece = new QGraphicsTextItem();

    blackPiece->setPos(1170,10);
    blackPiece->setZValue(1);
    blackPiece->setDefaultTextColor(Qt::black);
    blackPiece->setFont(QFont("",14));
    blackPiece->setPlainText("ФИГУРЫ ЧЕРНЫХ");
    addToScene(blackPiece);
    addToScene(check);
    chess->addChessPiece();
}

void Game::drawDeadHolder(int x, int y,QColor color)
{
    deadHolder = new QGraphicsRectItem(x,y,300,800);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    deadHolder->setBrush(brush);
    addToScene(deadHolder);
}

void Game::Check()
{
    check->setVisible(true);
}

void Game::restart()
{
    check->setVisible(false);
    alivePiece.clear();
    chess->reset();
    removeFromScene(restartButton);
    setTurn("WHITE");
    turnDisplay->setPlainText("ОЧЕРЕДЬ : WHITE");
    //start();
}

void Game::displayMainMenu()
{
    QGraphicsPixmapItem *p = new QGraphicsPixmapItem();
    p->setPixmap(QPixmap(":/images/king1.png"));
    p->setPos(900,170);
    addToScene(p);
    listG.append(p);

    QGraphicsPixmapItem *p1 = new QGraphicsPixmapItem();
    p1->setPixmap(QPixmap(":/images/king.png"));
    p1->setPos(440,170);
    addToScene(p1);
    listG.append(p1);
    //Create the title
    QGraphicsTextItem *titleText = new QGraphicsTextItem("ШАХМАТЫ");
    QFont titleFont("arial", 58);
    titleText->setDefaultTextColor(Qt::white);
    titleText->setFont( titleFont);
    QGraphicsRectItem *titleRect = new QGraphicsRectItem(width()/2-200,150,400,100);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(*new QColor(79,55,39));
    titleRect->setBrush(brush);
    addToScene(titleRect);
    listG.append(titleRect);
    int xPos = width()/2 - titleText->boundingRect().width()/2;
    int yPos = 150;
    titleText->setPos(xPos,yPos);
    addToScene(titleText);
    listG.append(titleText);
    //create Button
    Button * playButton = new Button("Играть");
    int pxPos = width()/2 - playButton->boundingRect().width()/2;
    int pyPos = 300;
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()) , this , SLOT(start()));
    addToScene(playButton);
    listG.append(playButton);

    //Create Quit Button
    Button * quitButton = new Button("Выход");
    int qxPos = width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 375;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close()));
    addToScene(quitButton);
    drawChessBoard();
    listG.append(quitButton);

    //Restart Button
    int rxPos = width()/2 - restartButton->boundingRect().width()/2;
    int ryPos = 300;
    restartButton->setPos(rxPos,ryPos);
    connect(restartButton,SIGNAL(clicked()) , this , SLOT(restart()));
    listG.append(restartButton);
}

void Game::gameOver(QString value)
{
    //removeAll();
    addToScene(restartButton);
    if(value=="checkmate") check->setPlainText("МАТ!");
    else check->setPlainText("ПАТ!");
    check->setVisible(true);
}


void Game::removeAll(){
    QList<QGraphicsItem*> itemsList = gameScene->items();
    for(size_t i = 0, n = itemsList.size();i<n;i++) {
        if(itemsList[i]!=check)
          removeFromScene(itemsList[i]);
    }
}

void Game::move(QString move)
{
    if(possibleMoves.contains(move))
    {
        QString mod="";
        //если рокировка
        if(move.contains("0-0") || move.contains("0-0-0"))
        {
            if(move[move.length()-1]!='0')
                mod=move[move.length()-1];
            chess->move("","",mod,move);
        }
        else
        {
            QString start(move[0]); start+=move[1];
            QString end(move[3]); end+=move[4];
            mod = chess->getMoveMod(chess->chooseBox(start),chess->chooseBox(end));
            chess->move(start,end,mod);
        }
    }
}

void Game::setLastMove(QString value)
{
    lastPlayerMove = value;
}

QString Game::getLastMove()
{
    return lastPlayerMove;
}
