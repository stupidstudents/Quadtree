#include "paint.h"
#include "ui_paint.h"

paint::paint(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::paint)
{
    ui->setupUi(this);

    quadTree = new QuadTree(nullptr, (float)ui->graphicsView->x(), (float)ui->graphicsView->y(), (float)ui->graphicsView->width() - 20);
    scene = new paintScene();
    scene->setQuadTree(quadTree);

    ui->graphicsView->setScene(scene);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &paint::slotTimer);
    timer->start(100);
}

paint::~paint()
{
    delete timer;
    delete scene;
    delete quadTree;
    delete ui;
}

void paint::slotTimer(){
    timer->stop();
    scene->setSceneRect(0,0,ui->graphicsView->width() - 20, ui->graphicsView->height() - 20);
}

void paint::resizeEvent(QResizeEvent *event){
    timer->start(100);
    QWidget::resizeEvent(event);
}

void paint::on_openFile_triggered()
{

}
