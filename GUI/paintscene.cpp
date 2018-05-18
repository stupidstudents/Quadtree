#include "paintscene.h"

paintScene::paintScene(QObject *parent) : QGraphicsScene(parent)
{
}

void paintScene::setQuadTree(QuadTree *quadTree) {
    this->quadTree = quadTree;
    labels = new QVector<CustomLabel *>();
}

paintScene::~paintScene()
{
    labels->clear();

    delete labels;
    delete quadTree;
}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Point p = { event->scenePos().x(),
                event->scenePos().y() };

    if (event->buttons() == Qt::LeftButton) {
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform() );

        if (item) {
            QGraphicsProxyWidget *labelProxy = dynamic_cast<QGraphicsProxyWidget*>(item);

            if (labelProxy) {
                CustomLabel *label = dynamic_cast<CustomLabel*>(labelProxy->widget());

                if (label) {
                    delete label;
                    labels->remove(labels->indexOf(label));
                    return;
                }
            }

        }

        if (quadTree->Insert(p) == INSERT_SUCCESS) {
            addEllipse(p.X - 2,
                       p.Y - 2,
                       4,
                       4,
                       QPen(Qt::NoPen),
                       QBrush(Qt::red));
            Draw(quadTree);
        }
    }
    else if (event->buttons() == Qt::RightButton) {
        std::vector<Point> points = quadTree->FindPointsArround(Quad {p.X - 4, p.Y - 4, 8});

        for (size_t i = 0; i < points.size(); i++) {
            addLabel(event->scenePos(), QString("test\nstring\ntest"));
        }
    }


    previousPoint = event->scenePos();
}

void paintScene::addLabel(QPointF p, const QString text) {
    CustomLabel *label = new CustomLabel(p, text);

    if (label->TryToInsert(this, labels))
        labels->push_back(label);
}

void paintScene::Draw(QuadTree *qTree) {
    if (qTree->q1) {
        addRect(qTree->q1->quad.p.X, qTree->q1->quad.p.Y, qTree->q1->quad.size, qTree->q1->quad.size, QPen(Qt::lightGray)); Draw(qTree->q1);
        addRect(qTree->q2->quad.p.X, qTree->q2->quad.p.Y, qTree->q2->quad.size, qTree->q2->quad.size, QPen(Qt::lightGray)); Draw(qTree->q2);
        addRect(qTree->q3->quad.p.X, qTree->q3->quad.p.Y, qTree->q3->quad.size, qTree->q3->quad.size, QPen(Qt::lightGray)); Draw(qTree->q3);
        addRect(qTree->q4->quad.p.X, qTree->q4->quad.p.Y, qTree->q4->quad.size, qTree->q4->quad.size, QPen(Qt::lightGray)); Draw(qTree->q4);
    }
}


