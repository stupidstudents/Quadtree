#include "customlabel.h"

CustomLabel::CustomLabel(std::vector<CustomLabel*> *labels, QWidget *parent) : QLabel(parent) {
    this->labels = labels;
    labels->push_back(this);
}

CustomLabel::~CustomLabel() {

}


void CustomLabel::addLabel(CustomLabel *label) {
    labels->push_back(label);
}

bool CustomLabel::checkIntersect() {
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
        else
            return false;
    }
}

