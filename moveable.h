#ifndef MOVEABLE_H
#define MOVEABLE_H

#include <QObject>
#include <QTimer>
#include <QGraphicsEllipseItem>
#include "direction.h"
#include "wall.h"

class Moveable : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Moveable(qreal size, qreal speed);


private:
    };

#endif // MOVEABLE_H
