#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QKeyEvent>
#include <QTimer>
#include "direction.h"
#include "pickup.h"
#include "enemy.h"
#include "gameboard.h"

const float PLAYER_SPEED = 1.5f;

class GameBoard;

class Player : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Player(qreal size, GameBoard* gameBoard);
    void keyPressEvent(QKeyEvent *event);
public slots:
    void move();
    void openCloseMouth();
private:
    QTimer* moveTimer = new QTimer();
    QTimer* animationTimer = new QTimer();
    GameBoard* gameBoard;
    Direction movingDirection;
    qreal size;

    void setMoveTimer();
    void setAnimationTimer();
    void detectColisions();
    void onWallCollision();
    void changeDirection(Direction direction);
    void onEnemyCollision();
    void onPickupCollision(Pickup* pickup);
    void unsafeMove();
    void tryToChangePosition(qreal x, qreal y);
};

#endif // PLAYER_H
