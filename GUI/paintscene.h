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

    void reDraw();
private:
    QuadTree *quadTree;
    QVector<CustomLabel *> *labels;
    long unsigned int z_ind = 1;

    void Draw(QuadTree *qTree, bool withPoints = false);
    void DrawPoints(QuadTree *q);

    void addLabel(Point *p, const QString text);
    CustomLabel* tryCastToCLabel(QPointF point);
    bool tryCloseLabel(CustomLabel *label);
    bool tryShowOnTop(CustomLabel *label);


    bool showPointTextInputDialog(std::string *text);

    void mousePressEvent(QGraphicsSceneMouseEvent * event);
};

#endif // PAINTSCENE_H
