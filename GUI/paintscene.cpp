#include "paintscene.h"

paintScene::paintScene(QuadTree *quadTree, QObject *parent) : QGraphicsScene(parent)
{
    this->quadTree = quadTree;
    labels = new QVector<CustomLabel *>();
}


paintScene::~paintScene()
{
    for (size_t i = 0; i < labels->size(); i++) {
        delete labels->at(i);
    }

    labels->clear();
    delete labels;
}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Point *p = new Point();
    p->X = event->scenePos().x();
    p->Y = event->scenePos().y();

    if (event->buttons() == Qt::LeftButton) {
        if (tryShowOnTop(tryCastToCLabel(event->scenePos()))) return;

        std::string point_text;
        if (showPointTextInputDialog(&point_text)) p->text = point_text;
        else return;

        if (quadTree->Insert(p) == INSERT_SUCCESS) {
            addEllipse(p->X - 2, p->Y - 2, 4, 4, QPen(Qt::NoPen), QBrush(Qt::red));
            Draw(quadTree);
        }
    }
    else if (event->buttons() == Qt::RightButton) {
        if (tryCloseLabel(tryCastToCLabel(event->scenePos()))) return;

        std::vector<Point*> points = quadTree->FindPointsArround(quadTree->MakeQuad(p->X - 4, p->Y - 4, 8));

        for (int i = 0; i < points.size(); i++) {
            if (points[i]->clicked) return;

            points[i]->clicked = true;
            addLabel(points[i], QString::fromUtf8(points[i]->text.c_str()));
        }
    }
}

void paintScene::addLabel(Point *p, const QString text) {
    CustomLabel *label = new CustomLabel(p, text, z_ind++);

    label->TryToInsert(this, labels);
    labels->push_back(label);
}

CustomLabel* paintScene::tryCastToCLabel(QPointF point) {
    QGraphicsItem *item = itemAt(point, QTransform() );

    if (item) {
        QGraphicsProxyWidget *labelProxy = dynamic_cast<QGraphicsProxyWidget*>(item);

        if (labelProxy) {
            CustomLabel *label = dynamic_cast<CustomLabel*>(labelProxy->widget());
            return label;
        }

    }

    return 0;
}

bool paintScene::tryCloseLabel(CustomLabel *label) {
    if (!label) return false;

    label->P()->clicked = false;
    labels->remove(labels->indexOf(label));
    delete label;

    return true;
}

bool paintScene::tryShowOnTop(CustomLabel *label) {
    if (!label) return false;

    label->setZIndex(z_ind++);
    return true;
}

bool paintScene::showPointTextInputDialog(std::string *text) {
    bool success;
    QString _text = QInputDialog::getText(0, tr("Enter point data"), tr("Data:"), QLineEdit::Normal, tr("Enter some text for label..."), &success);
    *text = _text.toUtf8().constData();

    return success;
}

void paintScene::reDraw() {
    if (quadTree) Draw(quadTree, true);
}

void paintScene::DrawPoints(QuadTree *q) {
    for (size_t i = 0; i < q->points.size(); i++) {
        addEllipse(q->points[i]->X - 2, q->points[i]->Y - 2, 4, 4, QPen(Qt::NoPen), QBrush(Qt::red));
    }
}

void paintScene::Draw(QuadTree *qTree, bool withPoints) {
    if (qTree->q1) {
        addRect(qTree->q1->quad.p.X, qTree->q1->quad.p.Y, qTree->q1->quad.size, qTree->q1->quad.size, QPen(Qt::lightGray)); Draw(qTree->q1, withPoints);
        addRect(qTree->q2->quad.p.X, qTree->q2->quad.p.Y, qTree->q2->quad.size, qTree->q2->quad.size, QPen(Qt::lightGray)); Draw(qTree->q2, withPoints);
        addRect(qTree->q3->quad.p.X, qTree->q3->quad.p.Y, qTree->q3->quad.size, qTree->q3->quad.size, QPen(Qt::lightGray)); Draw(qTree->q3, withPoints);
        addRect(qTree->q4->quad.p.X, qTree->q4->quad.p.Y, qTree->q4->quad.size, qTree->q4->quad.size, QPen(Qt::lightGray)); Draw(qTree->q4, withPoints);

        if (withPoints) {
            DrawPoints(qTree);
            DrawPoints(qTree->q1);
            DrawPoints(qTree->q2);
            DrawPoints(qTree->q3);
            DrawPoints(qTree->q4);
        }
    }
}




