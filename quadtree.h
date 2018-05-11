#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <stdio.h>

struct Point {
    float X;
    float Y;

    void Set(float X, float Y);
};
struct Quad {
    Point p;
    float size;

    bool ContainPoint(Point p);
    bool IntersectWithQuad(Quad q);
};

class QuadTree
{
public:
    QuadTree(QuadTree *parent, Quad quad);
    ~QuadTree();

    bool Insert(Point p);
    bool Divide();
    std::vector<Point> FindPointsArround(Quad q);

    void SetQuad(Quad q);
private:
    static const int POINT_COUNT = 1;
    std::vector<Point> points;
    bool filled = false;

    Quad quad;

    QuadTree *q1;
    QuadTree *q2;
    QuadTree *q3;
    QuadTree *q4;
    QuadTree *parent;
};

#endif // QUADTREE_H
