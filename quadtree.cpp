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

QuadTree::QuadTree(QuadTree *parent, float X, float Y, float size) {
    this->parent = parent;
    this->quad = Quad {X, Y, size};
}

QuadTree::~QuadTree() {
    delete q1;
    delete q2;
    delete q3;
    delete q4;
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

int Quad::ContainPoint(Point p) {
    if ( ((p.X > this->p.X) && (p.X < (this->p.X + this->size) )) && ( (p.Y > this->p.Y) && (p.Y < (this->p.Y + this->size)) )) return QUAD_CONTAIN;
    else if (
                ( ((p.X == this->p.X) || p.X == (this->p.X + this->size)) && (p.Y >= this->p.Y && p.Y <= this->p.Y + this->size) ) ||
                ( (p.Y == this->p.Y || p.Y == (this->p.Y + this->size))  &&  (p.X >= this->p.X && p.X <= this->p.X + this->size))
            ) return QUAD_BORDER_INTERSECT;
    else return QUAD_NOT_CONTAIN;
}

void QuadTree::Divide() {
    //Quad 1
    Quad qd1 = {quad.p, quad.size / 2};
    q1 = new QuadTree(this, qd1);

    //Quad2
    Quad qd2 = {quad.p.X + quad.size / 2, quad.p.Y, quad.size / 2};
    q2 = new QuadTree(this, qd2);

    //Quad3
    Quad qd3 = {quad.p.X, quad.p.Y + quad.size / 2, quad.size / 2};
    q3 = new QuadTree(this, qd3);

    //Quad4
    Quad qd4 = {quad.p.X + quad.size / 2, quad.p.Y + quad.size / 2, quad.size / 2};
    q4 = new QuadTree(this, qd4);
}

int QuadTree::Insert(Point p) {
    if (parent) {
        for (size_t i = 0; i < parent->points.size(); i++) {
            if (quad.ContainPoint(parent->points[i]) == QUAD_CONTAIN) {
                this->points.push_back(parent->points[i]);
                parent->points.erase(parent->points.begin() + i);
            }
        }
    }

    int pointCheckResult = quad.ContainPoint(p);
    if (pointCheckResult != QUAD_CONTAIN) {
        printf("Skiped: X-%f, Y-%f, QUAD->X-%f, Y-%f, Size-%f\n", p.X, p.Y, quad.p.X, quad.p.Y, quad.size);
        return pointCheckResult;
    }

    if (points.size() < POINT_COUNT && !filled) {
        points.push_back(p);
        return INSERT_SUCCESS;
    }
    else filled = true;

    if (!q1) Divide();

    if (q1->Insert(p) == INSERT_SUCCESS) return INSERT_SUCCESS;
    if (q2->Insert(p) == INSERT_SUCCESS) return INSERT_SUCCESS;
    if (q3->Insert(p) == INSERT_SUCCESS) return INSERT_SUCCESS;
    if (q4->Insert(p) == INSERT_SUCCESS) return INSERT_SUCCESS;

    return INSERT_FAIL;
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
