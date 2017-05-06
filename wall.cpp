#include "wall.h"

Wall::Wall(int x, int y, int width, int height) : QGraphicsRectItem(x, y, width, height)
{
    setBrush(QColor("grey"));
    setPen(Qt::NoPen);
}
