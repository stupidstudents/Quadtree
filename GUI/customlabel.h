#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QObject>
#include <QMouseEvent>
#include <QLabel>
#include <QWidget>
#include <QString>
#include <QDebug>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QtMath>

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(QPointF p, const QString &text, QVector<CustomLabel *> *labels, QWidget *parent = nullptr);
    ~CustomLabel();

    bool checkIntersect();
    bool TryToInsert(QGraphicsScene *scene);

    void addToScene(QGraphicsScene *scene, bool intersected);
private:
    QGraphicsLineItem *line;
    QPointF p;
    QVector<CustomLabel*> *labels;
    QGraphicsProxyWidget *proxy;

    QPointF MoveOnCircle(double step);
};

#endif // CUSTOMLABEL_H
