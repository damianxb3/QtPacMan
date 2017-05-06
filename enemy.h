#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QTimer>
#include "direction.h"
#include "wall.h"
#include "gameboard.h"

class GameBoard;

const float ENEMY_SPEED = 1.0f;

class Enemy : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    Enemy(qreal size, GameBoard* gameBoard);
public slots:
    void move();
    void changeShape();
private:
    GameBoard* gameBoard;
    Direction movingDirection;
    qreal size;
    bool state = true;

    void setMoveTimer();
    void setAnimationTimer();
    void detectColisions();
    void onWallCollision(Wall *wall);
    void changeDirection(Direction direction);
    void unsafeMove();
    void tryToChangePosition(qreal x, qreal y);
};

#endif // ENEMY_H
