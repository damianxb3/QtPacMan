#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QGraphicsScene>
#include "player.h"
#include "wall.h"
#include "pickup.h"
#include "enemy.h"

class Player;
class Pickup;
class Enemy;

const std::vector<std::vector<int>> gameBoard {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,0,1,1,1,1,1,1,1,1,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

class GameBoard : public QGraphicsScene
{
private:
    int rowsNumber;
    int columnsNumber;
    qreal wallFragmentWidth;
    qreal wallFragmentHeight;
    Player* player;

    void drawGameBoard();
    void addWalls();
    void addPlayer();
    void addEnemies();
    Enemy* createEnemy();
public:
    GameBoard(qreal x, qreal y, qreal width, qreal height);
};

#endif // GAMEBOARD_H
