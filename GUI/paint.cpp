#include "paint.h"
#include "ui_paint.h"
#include "readfile.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopWidget>

paint::paint(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::paint)
{
    ui->setupUi(this);

    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height()-  this->height()) / 2;
    this->move(x, y);

    quadTree = new QuadTree(0, (float)ui->graphicsView->x(), (float)ui->graphicsView->y(), (float)ui->graphicsView->width() - 20);
    scene = new paintScene(quadTree);

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
    ReadFile reader;
    std::vector<Point*> points;

    QString filename =  QFileDialog::getOpenFileName(
          this,
          "Open file with points",
          QDir::currentPath(),
          "Txt files (*.txt)");

    if( !filename.isNull() ) {
        if (reader.reading(filename.toUtf8().constData(), &points) == 1) {
            for (int i = 0; i < points.size() - 1; i++) {
                quadTree->Insert(points[i]);
            }
            scene->reDraw();
        }
        else {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Error reading file!");
            messageBox.setFixedSize(500,200);
        }
    }
}
