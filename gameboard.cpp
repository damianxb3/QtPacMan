#include "gameboard.h"

#define PLAYER_SIZE 30
#define ENEMY_SIZE 50

GameBoard::GameBoard(qreal x, qreal y, qreal width, qreal height) : QGraphicsScene(x, y, width, height)
{
    drawGameBoard();
    addPlayer();
    addEnemies();
    addGameOverText();
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
    player = new Player(PLAYER_SIZE, this);
    this->addItem(player);
    player->setPos(7 * wallFragmentWidth + (wallFragmentWidth - PLAYER_SIZE) / 2, 6 * wallFragmentHeight + (wallFragmentHeight - PLAYER_SIZE) / 2);
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
    while (randomRow == 6 || gameBoard[randomRow][randomColumn] == 1)
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

void GameBoard::addGameOverText()
{
    gameOverText->setFont(QFont("Times", 15, QFont::Bold));
    gameOverText->setDefaultTextColor(QColor("red"));
    gameOverText->setPos((width() - gameOverText->boundingRect().width()) / 2, (height() - gameOverText->boundingRect().height()) / 2);
    gameOverText->setVisible(false);
    addItem(gameOverText);
}

void GameBoard::showGameOverText()
{
    gameOverText->setVisible(true);
}
