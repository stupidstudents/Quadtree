#include "paintscene.h"

paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{
}

void paintScene::setQuadTree(QuadTree *quadTree) {
    this->quadTree = quadTree;
    labels = new std::vector<CustomLabel *>();
}

paintScene::~paintScene()
{
    delete labels;
}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Point p = {event->scenePos().x(), event->scenePos().y()};

    if (event->buttons() == Qt::LeftButton) {
        if (quadTree->Insert(p) == INSERT_SUCCESS) {
            addEllipse(p.X - 2,
                       p.Y - 2,
                       4,
                       4,
                       QPen(Qt::NoPen),
                       QBrush(Qt::red));
            Draw(quadTree);

            CustomLabel *label1 = new CustomLabel(labels);
            label1->setText("bla");
            label1->setGeometry(QRect(10, 10, 100, 20));

            CustomLabel *label2 = new CustomLabel(labels);
            label2->setText("bla1");
            label2->setGeometry(QRect(150, 150, 100, 20));

            qDebug() <<label1->checkIntersect() <<"\n";
            //addWidget(label);
        }
    }
    else if (event->buttons() == Qt::RightButton) {
        std::vector<Point> points = quadTree->FindPointsArround(Quad {p.X - 2, p.Y - 2, 4});

        if (points.size() == 0) qDebug() <<"Points not found!\n";

        for (size_t i = 0; i < points.size(); i++) {
            qDebug() << "Find: X-" <<points[i].X << ", Y-" << points[i].Y <<"\n";
        }
    }


    previousPoint = event->scenePos();
}

void paintScene::Draw(QuadTree *qTree) {
    if (qTree->q1) {
        addRect(qTree->q1->quad.p.X, qTree->q1->quad.p.Y, qTree->q1->quad.size, qTree->q1->quad.size, QPen(Qt::lightGray)); Draw(qTree->q1);
        addRect(qTree->q2->quad.p.X, qTree->q2->quad.p.Y, qTree->q2->quad.size, qTree->q2->quad.size, QPen(Qt::lightGray)); Draw(qTree->q2);
        addRect(qTree->q3->quad.p.X, qTree->q3->quad.p.Y, qTree->q3->quad.size, qTree->q3->quad.size, QPen(Qt::lightGray)); Draw(qTree->q3);
        addRect(qTree->q4->quad.p.X, qTree->q4->quad.p.Y, qTree->q4->quad.size, qTree->q4->quad.size, QPen(Qt::lightGray)); Draw(qTree->q4);
    }
}


