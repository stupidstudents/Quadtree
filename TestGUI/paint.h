#ifndef PAINT_H
#define PAINT_H

#include <QMainWindow>

namespace Ui {
class paint;
}

class paint : public QMainWindow
{
    Q_OBJECT

public:
    explicit paint(QWidget *parent = 0);
    ~paint();

private:
    Ui::paint *ui;
};

#endif // PAINT_H
