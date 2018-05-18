#ifndef PAINT_H
#define PAINT_H

#include <QMainWindow>
#include <QTimer>
#include <QResizeEvent>
#include "quadtree.h"

#include <paintscene.h>
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
    QTimer *timer;      /* Определяем таймер для подготовки актуальных размеров
                            * графической сцены
                            * */
    paintScene *scene;
    QuadTree *quadTree;

private:
    /* Переопределяем событие изменения размера окна
         * для пересчёта размеров графической сцены
         * */
    void resizeEvent(QResizeEvent * event);

private slots:
    void slotTimer();
    void on_openFile_triggered();
};

#endif // PAINT_H
