#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTimer>
#include <QDebug>
#include "quadtree.h"

class paintScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit paintScene(QObject *parent = 0);
    void setQuadTree(QuadTree *quadTree);
    void Draw(QuadTree *qTree);
    ~paintScene();

private:
    QPointF     previousPoint;  // Координаты предыдущей точки
    QuadTree *quadTree;

private:
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

};

#endif // PAINTSCENE_H
