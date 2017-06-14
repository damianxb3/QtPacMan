#ifndef PACMANGRAPHICSVIEW_H
#define PACMANGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>

class PacmanGraphicsView : public QGraphicsView
{
public:
    PacmanGraphicsView(QGraphicsScene* scene);
};

#endif // PACMANGRAPHICSVIEW_H
