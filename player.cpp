#include <QDebug>
#include "player.h"

Player::Player(qreal size, GameBoard* gameBoard)
{
    this->gameBoard = gameBoard;
    movingDirection = RIGHT;
    setRect(0, 0, size, size);
    setTransformOriginPoint(QPoint(size/2, size/2));
    setStartAngle(25 * 16);
    setBrush(QColor("yellow"));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    setMoveTimer();
    setAnimationTimer();
}

void Player::setMoveTimer()
{
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(10);
}

void Player::setAnimationTimer()
{
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(openCloseMouth()));
    animationTimer->start(250);
}

void Player::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_Right:
            changeDirection(RIGHT);
            break;
        case Qt::Key_Left:
            changeDirection(LEFT);
            break;
        case Qt::Key_Up:
            changeDirection(UP);
            break;
        case Qt::Key_Down:
            changeDirection(DOWN);
            break;
    }
}

void Player::move()
{
    detectColisions();
    unsafeMove();
}

void Player::detectColisions()
{
    foreach (QGraphicsItem* item, collidingItems())
    {
        if (qgraphicsitem_cast<Wall*>(item) != NULL)
        {
            onWallCollision();
            break;
        }
        if (qgraphicsitem_cast<Enemy*>(item) != NULL)
        {
            onEnemyCollision();
            break;
        }

        Pickup* pickup = qgraphicsitem_cast<Pickup*>(item);
        if (pickup != NULL)
        {
            onPickupCollision(pickup);
            break;
        }
    }
}

void Player::onWallCollision()
{
    if (movingDirection == UP)
    {

        qDebug() << "UPcollision";
        tryToChangePosition(x(), y() + PLAYER_SPEED);
        changeDirection(DOWN);
    }
    else if (movingDirection == DOWN)
    {
        qDebug() << "DOWNcollision";
        tryToChangePosition(x(), y() - PLAYER_SPEED);
        changeDirection(UP);
    }
    else if (movingDirection == RIGHT)
    {
        tryToChangePosition(x() - PLAYER_SPEED, y());
        changeDirection(LEFT);
    }
    else if (movingDirection == LEFT)
    {
        tryToChangePosition(x() + PLAYER_SPEED, y());
        changeDirection(RIGHT);
    }
}

void Player::changeDirection(Direction direction)
{
    movingDirection = direction;
    switch (direction) {
        case LEFT:
            setRotation(180);
            break;
        case RIGHT:
            setRotation(0);
            break;
        case UP:
            setRotation(270);
            break;
        case DOWN:
            setRotation(90);
            break;
        }
}

void Player::onEnemyCollision()
{
    moveTimer->stop();
    animationTimer->stop();
    setSpanAngle(310 * 16);
    gameBoard->showGameOverText();
}

void Player::onPickupCollision(Pickup* pickup)
{
    scene()->removeItem(pickup);
    delete pickup;
}

void Player::unsafeMove()
{
    switch (movingDirection) {
        case UP:
            tryToChangePosition(x(), y() - PLAYER_SPEED);
            break;
        case DOWN:
            tryToChangePosition(x(), y() + PLAYER_SPEED);
            break;
        case LEFT:
             tryToChangePosition(x() - PLAYER_SPEED, y());
            break;
        case RIGHT:
            tryToChangePosition(x() + PLAYER_SPEED, y());
            break;
    }
}

void Player::tryToChangePosition(qreal x, qreal y)
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

void Player::openCloseMouth()
{
    static bool open = false;
    open = !open;
    setSpanAngle(open ? 310 * 16 : 360 * 16);
}
