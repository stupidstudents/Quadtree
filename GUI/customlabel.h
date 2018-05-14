#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QObject>
#include <QLabel>
#include <QWidget>
#include <QString>

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(std::vector<CustomLabel*> *labels, QWidget *parent = nullptr);
    ~CustomLabel();

    void addLabel(CustomLabel *label);
    bool checkIntersect();
private:

    std::vector<CustomLabel*> *labels;
};

#endif // CUSTOMLABEL_H
