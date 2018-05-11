#include "quadtree.h"

using namespace std;

void InsertInVector(vector<Point> *b, vector<Point> e) {
    b->insert(b->end(), e.begin(), e.end());
}

QuadTree::QuadTree(QuadTree *parent, Quad quad)
{
    this->parent = parent;
    this->quad = quad;
}

QuadTree::~QuadTree() {
    delete q1;
    delete q2;
    delete q3;
    delete q4;
}

void QuadTree::SetQuad(Quad quad) {
    this->quad = quad;
}

bool Quad::IntersectWithQuad(Quad q) {
    if(
        (this->p.X > q.p.X && this->p.X < (q.p.X + q.size)) ||
        ((this->p.X + this->size) > q.p.X && (this->p.X + this->size) < (q.p.X + q.size)) ||
        (this->p.Y > q.p.Y && this->p.Y < (q.p.Y + q.size)) ||
        ((this->p.Y + this->size) > q.p.Y && (this->p.Y + this->size) < (q.p.Y + q.size)) ||
        (q.p.X > this->p.X && q.p.X < (this->p.X + this->size)) ||
        ((q.p.X + q.size) > this->p.X && (q.p.X + q.size) < (this->p.X + this->size)) ||
        (q.p.Y > this->p.Y && q.p.Y < (this->p.Y + this->size)) ||
        ((q.p.Y + q.size) > this->p.Y && (q.p.Y + q.size) < (this->p.Y + this->size))
      )
        return true;
    else
        return false;
}

bool Quad::ContainPoint(Point p) {
    if ( ((p.X > this->p.X) && (p.X < this->p.X + this->size)) && ( (p.Y > this->p.Y) && (p.Y < this->p.Y + this->size) ) ) return true;
    else return false;
}

bool QuadTree::Divide() {
    Quad qd;

    //Quad 1
    qd = quad;
    qd.size = quad.size / 2;
    q1 = new QuadTree(this, qd);

    //Quad2
    qd.p.X = qd.p.X + quad.size / 2;
    q2 = new QuadTree(this, qd);

    //Quad4
    qd.p.Y = qd.p.Y + quad.size / 2;
    q4 = new QuadTree(this, qd);

    //Quad3
    qd.p.X = quad.p.X;
    qd.p.Y = quad.p.Y + quad.size / 2;
    q3 = new QuadTree(this, qd);

    printf("Divided: \n");
    printf("X-%f, Y-%f, Size-%f\n", q1->quad.p.X, q1->quad.p.Y, q1->quad.size);
    printf("X-%f, Y-%f, Size-%f\n", q2->quad.p.X, q2->quad.p.Y, q2->quad.size);
    printf("X-%f, Y-%f, Size-%f\n", q3->quad.p.X, q3->quad.p.Y, q3->quad.size);
    printf("X-%f, Y-%f, Size-%f\n", q4->quad.p.X, q4->quad.p.Y, q4->quad.size);
}

bool QuadTree::Insert(Point p) {
    if (parent) {
        for (size_t i = 0; i < parent->points.size(); i++) {
            if (quad.ContainPoint(parent->points[i])) {
                this->points.push_back(parent->points[i]);
                parent->points.erase(parent->points.begin() + i);
            }
        }
    }

    if (!quad.ContainPoint(p)) {
        printf("Skiped: X-%f, Y-%f, QUAD->X-%f, Y-%f, Size-%f\n", p.X, p.Y, quad.p.X, quad.p.Y, quad.size);
        return false;
    }

    if (points.size() < POINT_COUNT && !filled) {
        points.push_back(p);

        printf("Inserted: X-%f, Y-%f, QUAD->X-%f, Y-%f, Size-%f\n", p.X, p.Y, quad.p.X, quad.p.Y, quad.size);

        return true;
    }
    else filled = true;

    if (!q1) Divide();

    if (q1->Insert(p)) return true;
    if (q2->Insert(p)) return true;
    if (q3->Insert(p)) return true;
    if (q4->Insert(p)) return true;

    return false;
}

vector<Point> QuadTree::FindPointsArround(Quad q) {
    vector<Point> pointsInQuad;

    if (!quad.IntersectWithQuad(q)) return pointsInQuad;

    for (size_t i = 0; i < points.size(); i++) {
        if (q.ContainPoint(points[i])) pointsInQuad.push_back(points[i]);
    }

    if (!q1) return pointsInQuad;

    InsertInVector(&pointsInQuad, q1->FindPointsArround(q));
    InsertInVector(&pointsInQuad, q2->FindPointsArround(q));
    InsertInVector(&pointsInQuad, q3->FindPointsArround(q));
    InsertInVector(&pointsInQuad, q4->FindPointsArround(q));

    return pointsInQuad;
}
