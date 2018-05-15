#include "customlabel.h"

CustomLabel::CustomLabel(QPointF p, const QString &text, QGraphicsScene *scene, QWidget *parent) : QLabel(parent) {
    //УБРАТЬ!
    QFontMetrics metrics(this->font());

    setText(metrics.elidedText(text, Qt::ElideRight, 100));

    //УБРАТЬ

    //setText(text);

    QGraphicsProxyWidget *proxy = scene->addWidget(this);
    proxy->setPos(p.x() + 20, p.y() + 20);

    line = scene->addLine(p.x(), p.y(), p.x() + 20, p.y() + 20, QPen(Qt::lightGray));
}

CustomLabel::~CustomLabel() {

}

void CustomLabel::Close() {
    delete line;
    delete this;
}

bool CustomLabel::checkIntersect(std::vector<CustomLabel*> *labels) {
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
}

