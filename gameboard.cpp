#include "gameboard.h"

#define PLAYER_SIZE 35
#define ENEMY_SIZE 50

GameBoard::GameBoard(qreal x, qreal y, qreal width, qreal height) : QGraphicsScene(x, y, width, height)
{
    drawGameBoard();
    addPlayer();
    addEnemies();
}

void GameBoard::drawGameBoard()
{
    rowsNumber = (int) gameBoard.size();
    columnsNumber = (int) gameBoard[0].size();
    wallFragmentWidth = width() / columnsNumber;
    wallFragmentHeight = height() / rowsNumber;
    addWalls();
}

void GameBoard::addWalls()
{
    for (int row = 0; row < rowsNumber; row++)
    {
        for (int column = 0; column < columnsNumber; column++)
        {
            if (gameBoard[row][column] == 1)
            {
                Wall* wall = new Wall(column * wallFragmentWidth, row * wallFragmentHeight, wallFragmentWidth, wallFragmentHeight);
                addItem(wall);
            }
            else
            {
                Pickup* pickup = new Pickup((column + 0.4) * wallFragmentWidth, (row + 0.4) * wallFragmentHeight, 10, 10);
                addItem(pickup);
            }
        }
    }
}

void GameBoard::addPlayer()
{
    player = new Player(PLAYER_SIZE);
    this->addItem(player);
    player->setPos(400, 300);
}

void GameBoard::addEnemies()
{
    for (int i = 0; i < 4; i++)
    {
        Enemy* enemy = createEnemy();
        this->addItem(enemy);
    }
}

Enemy* GameBoard::createEnemy()
{
    int randomRow = qrand() % rowsNumber;
    int randomColumn = qrand() % columnsNumber;
    while (gameBoard[randomRow][randomColumn] == 1)
    {
        randomRow = qrand() % gameBoard.size();
        randomColumn = qrand() % gameBoard[0].size();
    }

    const int wallFragmentWidth = width() / columnsNumber;
    const int wallFragmentHeight = height() / rowsNumber;
    Enemy* enemy = new Enemy(ENEMY_SIZE, this);
    enemy->setPos(randomColumn * wallFragmentWidth, randomRow * wallFragmentHeight);
    return enemy;
}
