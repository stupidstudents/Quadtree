#include "paintscene.h"

paintScene::paintScene(QuadTree *quadTree, QObject *parent) : QGraphicsScene(parent)
{
    this->quadTree = quadTree;
    labels = new QVector<CustomLabel *>();
}


paintScene::~paintScene()
{
    labels->clear();
    delete labels;
}

void paintScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Point p = { event->scenePos().x(),
                event->scenePos().y() };

    if (event->buttons() == Qt::LeftButton) {
        if (tryCloseLabel(event->scenePos())) return;

        p.text = showPointTextInputDialog();
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
        std::vector<Point> points = quadTree->FindPointsArround(Quad {p.X - 4, p.Y - 4, "", 8});

        for (size_t i = 0; i < points.size(); i++) {
            addLabel(event->scenePos(), QString::fromUtf8(points[i].text.c_str()));
        }
    }


    previousPoint = event->scenePos();
}

void paintScene::addLabel(QPointF p, const QString text) {
    CustomLabel *label = new CustomLabel(p, text, z_ind++);

    label->TryToInsert(this, labels);
    labels->push_back(label);
}

bool paintScene::tryCloseLabel(QPointF point) {
    QGraphicsItem *item = itemAt(point, QTransform() );

    if (item) {
        QGraphicsProxyWidget *labelProxy = dynamic_cast<QGraphicsProxyWidget*>(item);

        if (labelProxy) {
            CustomLabel *label = dynamic_cast<CustomLabel*>(labelProxy->widget());

            if (label) {
                labels->remove(labels->indexOf(label));
                delete label;
                return true;
            }
        }

    }

    return false;
}

std::string paintScene::showPointTextInputDialog() {
    bool success;
    QString text = QInputDialog::getText(nullptr, tr("Enter point data"), tr("Data:"), QLineEdit::Normal, tr("Enter some text for label..."), &success);

    return text.toUtf8().constData();
}

void paintScene::Draw(QuadTree *qTree) {
    if (qTree->q1) {
        addRect(qTree->q1->quad.p.X, qTree->q1->quad.p.Y, qTree->q1->quad.size, qTree->q1->quad.size, QPen(Qt::lightGray)); Draw(qTree->q1);
        addRect(qTree->q2->quad.p.X, qTree->q2->quad.p.Y, qTree->q2->quad.size, qTree->q2->quad.size, QPen(Qt::lightGray)); Draw(qTree->q2);
        addRect(qTree->q3->quad.p.X, qTree->q3->quad.p.Y, qTree->q3->quad.size, qTree->q3->quad.size, QPen(Qt::lightGray)); Draw(qTree->q3);
        addRect(qTree->q4->quad.p.X, qTree->q4->quad.p.Y, qTree->q4->quad.size, qTree->q4->quad.size, QPen(Qt::lightGray)); Draw(qTree->q4);
    }
}


