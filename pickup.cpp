#include "pickup.h"

Pickup::Pickup(int x, int y, int width, int height)
{
    setTransformOriginPoint(width/2, height/2);
    setRect(x, y, width, height);
    setBrush(QColor("green"));
    setPen(Qt::NoPen);
}
