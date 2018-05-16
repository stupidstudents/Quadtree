#include "customlabel.h"

CustomLabel::CustomLabel(QPointF p, const QString &text, QVector<CustomLabel *> *labels, QWidget *parent) : QLabel(parent) {
    this->p = p;
    this->labels = labels;
    setText(text);
}

CustomLabel::~CustomLabel() {
    delete line;
}

/*bool CustomLabel::checkIntersect() {
    for (size_t i = 0; i < labels->size(); i++) {
        if(
                (geometry().x() > labels->at(i)->geometry().x() && geometry().x() < (labels->at(i)->geometry().x() + labels->at(i)->geometry().width())) ||
                ((geometry().x() + geometry().width()) > labels->at(i)->geometry().x() && (geometry().x() + geometry().width()) < (labels->at(i)->geometry().x() + labels->at(i)->geometry().width())) ||
                (geometry().y() > labels->at(i)->geometry().y() && geometry().y() < (labels->at(i)->geometry().y() + labels->at(i)->geometry().height())) ||
                ((geometry().y() + geometry().height()) > labels->at(i)->geometry().y() && (geometry().y() + geometry().height()) < (labels->at(i)->geometry().y() + labels->at(i)->geometry().height())) ||
                (labels->at(i)->geometry().x() > geometry().x() && labels->at(i)->geometry().x() < (geometry().x() + geometry().width())) ||
                ((labels->at(i)->geometry().x() + labels->at(i)->geometry().width()) > geometry().x() && (labels->at(i)->geometry().x() + labels->at(i)->geometry().width()) < (geometry().x() + geometry().width())) ||
                (labels->at(i)->geometry().y() > geometry().y() && labels->at(i)->geometry().y() < (geometry().y() + geometry().height())) ||
            ((labels->at(i)->geometry().y() + labels->at(i)->geometry().height()) > geometry().y() && (labels->at(i)->geometry().y() + labels->at(i)->geometry().height()) < (geometry().y() + geometry().height()))
          )
            return true;
    }

    return false;
}*/

bool CustomLabel::checkIntersect() {
    qDebug() << "\n" <<proxy->geometry();
    qDebug() <<"---------";
    for (size_t i = 0; i < labels->size(); i++) {
        qDebug() <<labels->at(i)->proxy->geometry();
        if (proxy->geometry().intersects(labels->at(i)->geometry())) return true;
    }

    return false;
}



bool CustomLabel::TryToInsert(QGraphicsScene *scene) {
    proxy = scene->addWidget(this);

    for (double angle = 0; angle < 360; angle += 10) {
        proxy->setPos(MoveOnCircle(angle));

        if (!checkIntersect()) {
            addToScene(scene, false);

            return true;
        }
    }
    addToScene(scene, true);
    return false;
}

QPointF CustomLabel::MoveOnCircle(double step) {
    QPointF point;

    point.setX(p.x() + 20 * qCos(qDegreesToRadians(step)));
    point.setY(p.y() + 20 * qSin(qDegreesToRadians(step)));

    return point;
}

void CustomLabel::addToScene(QGraphicsScene *scene, bool intersected) {
    line = scene->addLine(p.x(), p.y(), proxy->geometry().x(), proxy->geometry().y(), QPen(Qt::lightGray));
    if (intersected) proxy->widget()->setStyleSheet("QLabel {background-color: red;}");
}

