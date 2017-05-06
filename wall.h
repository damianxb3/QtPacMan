#ifndef WALL_H
#define WALL_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>

class Wall : public QGraphicsRectItem
{
public:
    Wall(int x, int y, int width, int height);
};

#endif // WALL_H
