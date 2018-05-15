#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include <QTimer>
#include <QDebug>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QTransform>
#include "quadtree.h"
#include "customlabel.h"

class paintScene : public QGraphicsScene
{

    Q_OBJECT

public:
    explicit paintScene(QObject *parent = 0);
    void setQuadTree(QuadTree *quadTree);
    void Draw(QuadTree *qTree);
    void addLabel(QPointF p, const QString text);
    ~paintScene();

private:
    QPointF     previousPoint;  // Координаты предыдущей точки
    QuadTree *quadTree;
    std::vector<CustomLabel*> *labels;

private:
    // Для рисования используем события мыши
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

};

#endif // PAINTSCENE_H
