#include "paintscene.h"

paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{
}

void paintScene::setQuadTree(QuadTree *quadTree) {
    this->quadTree = quadTree;
}

paintScene::~paintScene()
{

}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Point p = {event->scenePos().x(), event->scenePos().y()};
    // При нажатии кнопки мыши отрисовываем эллипс
    // Сохраняем координаты точки нажатия

    if (quadTree->Insert(p) == INSERT_SUCCESS) {
        addEllipse(p.X - 2,
                   p.Y - 2,
                   4,
                   4,
                   QPen(Qt::NoPen),
                   QBrush(Qt::red));
        Draw(quadTree);
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


