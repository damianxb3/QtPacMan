#include "enemy.h"
#include <QDebug>

Enemy::Enemy(qreal size, GameBoard* gameBoard)
{
    this->size = size;
    this->gameBoard = gameBoard;
    movingDirection = static_cast<Direction>(rand() % 3);
    QPolygonF polygon;
    polygon << QPointF(0, 0) << QPointF(size, 0) << QPointF(size, size) << QPointF(0, size);
    setPolygon(polygon);

    setBrush(QColor("blue"));
    setPen(Qt::NoPen);

    setMoveTimer();
    setAnimationTimer();
}

void Enemy::setMoveTimer()
{
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
}

void Enemy::setAnimationTimer()
{
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(changeShape()));
    timer->start(1000);
}

void Enemy::move()
{
    detectColisions();
    unsafeMove();
}

void Enemy::detectColisions()
{
    qreal xNew = x();
    qreal yNew = y();
    switch (movingDirection) {
        case UP:
            yNew -= ENEMY_SPEED;
            break;
        case DOWN:
            yNew += ENEMY_SPEED;
            break;
        case LEFT:
            xNew -= ENEMY_SPEED;
            break;
        case RIGHT:
            xNew += ENEMY_SPEED;
            break;
    }

    foreach (QGraphicsItem* item, collidingItems())
    {
        Wall* wall = qgraphicsitem_cast<Wall*>(item);
        if (wall != NULL)
        {
            onWallCollision(wall);
        }
    }
}

void Enemy::onWallCollision(Wall* wall)
{
    if (movingDirection == UP)
    {
        tryToChangePosition(x(), y() + ENEMY_SPEED);
        changeDirection(qrand() % 2 == 0 ? LEFT : RIGHT);
    }
    else if (movingDirection == DOWN)
    {
        tryToChangePosition(x(), y() - ENEMY_SPEED);
        changeDirection(qrand() % 2 == 0 ? LEFT: RIGHT);
    }
    else if (movingDirection == RIGHT)
    {
        tryToChangePosition(x() - ENEMY_SPEED, y());
        changeDirection(qrand() % 2 == 0 ? DOWN : UP);
    }
    else if (movingDirection == LEFT)
    {
        tryToChangePosition(x() + ENEMY_SPEED, y());
        changeDirection(qrand() % 2 == 0 ? DOWN : UP);
    }
}

void Enemy::changeDirection(Direction direction)
{
    movingDirection = direction;
}

void Enemy::unsafeMove()
{
    switch (movingDirection) {
        case UP:
            tryToChangePosition(x(), y() - ENEMY_SPEED);
            break;
        case DOWN:
            tryToChangePosition(x(), y() + ENEMY_SPEED);
            break;
        case LEFT:
             tryToChangePosition(x() - ENEMY_SPEED, y());
            break;
        case RIGHT:
            tryToChangePosition(x() + ENEMY_SPEED, y());
            break;
    }
}

void Enemy::tryToChangePosition(qreal x, qreal y)
{
    if (x < 0)
    {
        setPos(scene()->width(), y);
    }
    else if (x > scene()->width())
    {
        setPos(0, y);
    }
    else if (y < 0)
    {
        setPos(x, scene()->height());
    }
    else if (y > scene()->height())
    {
        setPos(x, 0);
    }
    else
    {
        setPos(x, y);
    }
}

void Enemy::changeShape()
{
    QPolygonF polygon;
    if (state)
    {
        polygon << QPointF(0, 0) << QPointF(size, 0) << QPointF(0, size) << QPointF(size, size);
    }
    else
    {
        polygon << QPointF(0, 0) << QPointF(size, 0) << QPointF(size, size) << QPointF(0, size);
    }
    setPolygon(polygon);

    state = !state;
}
