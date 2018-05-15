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

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(QPointF p, const QString &text, QGraphicsScene *scene, QWidget *parent = nullptr);
    ~CustomLabel();

    bool checkIntersect(std::vector<CustomLabel*> *labels);
    void Test();
private:
    const int Type = 99;
};

#endif // CUSTOMLABEL_H
