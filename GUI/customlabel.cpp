#include "customlabel.h"

CustomLabel::CustomLabel(Point *p, const QString &text, long unsigned int z_ind, QWidget *parent) : QLabel(parent) {
    this->p = p;
    this->z_ind = z_ind;

    setStyleSheet("QLabel {border: 1px solid gray; border-radius: 4px; background-color: #90FFDC;}");
    setFont(QFont("Arial", 10, 500));
    setText(text);
}

CustomLabel::~CustomLabel() {
    delete line;
    delete dot;
}

Point* CustomLabel::P() {
    return p;
}

bool CustomLabel::checkIntersect(QVector<CustomLabel *> *labels) {
    for (int i = 0; i < labels->size(); i++) {
        if (proxy->geometry().intersects(labels->at(i)->geometry())) return true;
    }

    return false;
}

bool CustomLabel::isInScene(QGraphicsScene *scene) {
    if (scene->sceneRect().contains(proxy->geometry())) return true;
    else return false;
}

bool CustomLabel::TryToInsert(QGraphicsScene *scene, QVector<CustomLabel *> *labels) {
    proxy = scene->addWidget(this);
    proxy->setZValue(z_ind);

    for (double angle = 0; angle < 360; angle += 10) {
        previousPoint = MoveOnCircle(angle);
        QPointF circlePoint = previousPoint;

        if (angle >= 0 && angle < 90) ChangeCoords(&previousPoint, 0, -proxy->geometry().height());
        else if (angle >= 90 && angle < 180) ChangeCoords(&previousPoint, -proxy->geometry().width(), -proxy->geometry().height());
        else if (angle >= 180 && angle < 270) ChangeCoords(&previousPoint, -proxy->geometry().width(), 0);
        else if (angle >= 270 && angle < 360) ChangeCoords(&previousPoint, 0, 0);

        proxy->setPos(previousPoint);

        if (angle != 0 && angle != 180) {
            for (size_t i = 0; i < SideStep; i++) {
                MoveBySide(angle, proxy->geometry().width() / SideStep, 0);

                if (!checkIntersect(labels) && isInScene(scene)) {
                    addToScene(scene, &circlePoint);
                    return true;
                }
            }
        }

        proxy->setPos(previousPoint);

        if (angle != 90 && angle != 270) {
            for (size_t i = 0; i < SideStep; i++) {
                MoveBySide(angle, 0, proxy->geometry().height() / SideStep);

                if (!checkIntersect(labels) && isInScene(scene)) {
                    addToScene(scene, &circlePoint);
                    return true;
                }
            }
        }

    }
    addToScene(scene, 0);
    return false;
}

QPointF CustomLabel::MoveOnCircle(double step) {
    QPointF point;

    point.setX(p->X + Radius * qCos(qDegreesToRadians(-step)));
    point.setY(p->Y + Radius * qSin(qDegreesToRadians(-step)));

    return point;
}

void CustomLabel::MoveBySide(double angle, double wStep, double hStep) {
    QPointF point = proxy->pos();

    if (angle >= 0 && angle < 90) {
        //Первая четверть
        ChangeCoords(&point, -wStep, hStep);
    }
    else if (angle >= 90 && angle < 180) {
        //Вторая четверть
        ChangeCoords(&point, wStep, hStep);
    }
    else if (angle >= 180 && angle < 270) {
        //Третья четверть
        ChangeCoords(&point, wStep, -hStep);
    }
    else if (angle >= 270 && angle < 360) {
        ChangeCoords(&point, -wStep, -hStep);
    }

    proxy->setPos(point);
}

void CustomLabel::ChangeCoords(QPointF *point, qreal delX, qreal delY) {
    point->setX(point->x() + delX);
    point->setY(point->y() + delY);
}

void CustomLabel::setZIndex(unsigned long z_ind) {
    this->z_ind = z_ind;

    proxy->setZValue(z_ind);
    line->setZValue(z_ind);
    dot->setZValue(z_ind);
}

void CustomLabel::addToScene(QGraphicsScene *scene, QPointF *point) {
    QPen pen(Qt::black, 1);
    QPointF cPoint;

    if (!point) {
        cPoint = MoveOnCircle(0);
        proxy->widget()->setStyleSheet("QLabel {background-color: #FF9999; border: 1px solid black;}");
    }
    else {
        cPoint = *point;
    }

    line = scene->addLine(p->X, p->Y, cPoint.x(), cPoint.y(), pen);
    dot = scene->addEllipse(cPoint.x() - 2, cPoint.y() - 2, 4, 4, Qt::NoPen, Qt::black);

    line->setZValue(z_ind);
    dot->setZValue(z_ind);
}
