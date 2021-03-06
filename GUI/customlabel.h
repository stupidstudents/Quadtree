#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QtMath>
#include "quadtree.h"

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(Point *p, const QString &text, long unsigned int z_ind, QWidget *parent = 0);
    ~CustomLabel();

    bool TryToInsert(QGraphicsScene *scene, QVector<CustomLabel *> *labels);
    void setZIndex(long unsigned int z_ind);

    Point* P();
private:
    const unsigned int Radius = 30;
    const unsigned int SideStep = 10;

    long unsigned int z_ind;

    Point *p;

    QGraphicsLineItem *line;
    QGraphicsEllipseItem *dot;
    QGraphicsProxyWidget *proxy;
    QPointF previousPoint;

    QPointF MoveOnCircle(double step);
    void MoveBySide(double angle, double wStep, double hStep);
    void ChangeCoords(QPointF *point, qreal x, qreal y);

    bool checkIntersect(QVector<CustomLabel *> *labels);
    bool isInScene(QGraphicsScene *scene);
    void addToScene(QGraphicsScene *scene, QPointF *point);
};

#endif // CUSTOMLABEL_H
