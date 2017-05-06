#ifndef PICKUP_H
#define PICKUP_H

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>

class Pickup : public QGraphicsEllipseItem
{
public:
    Pickup(int x, int y, int width, int height);
};

#endif // PICKUP_H
