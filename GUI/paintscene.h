#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QInputDialog>

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include <QLabel>
#include <QTransform>
#include "quadtree.h"
#include "customlabel.h"

class paintScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit paintScene(QuadTree *quadTree, QObject *parent = 0);
    ~paintScene();

private:
    QPointF previousPoint;
    QuadTree *quadTree;
    QVector<CustomLabel *> *labels;
    long unsigned int z_ind = 1;

    void Draw(QuadTree *qTree);

    void addLabel(QPointF p, const QString text);
    bool tryCloseLabel(QPointF point);

    std::string showPointTextInputDialog();

    void mousePressEvent(QGraphicsSceneMouseEvent * event);
};

#endif // PAINTSCENE_H
