#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <stdio.h>

#define INSERT_FAIL -1
#define INSERT_SUCCESS 0
#define QUAD_BORDER_INTERSECT 1
#define QUAD_CONTAIN 2
#define QUAD_NOT_CONTAIN 3

struct Point {
    float X;
    float Y;
};

struct Quad {
    Point p;
    float size;

    int ContainPoint(Point p);
    bool IntersectWithQuad(Quad q);
};

class QuadTree
{
public:
    QuadTree(QuadTree *parent, Quad quad);
    QuadTree(QuadTree *parent, float X, float Y, float size);
    ~QuadTree();

    int Insert(Point p);
    void Divide();
    std::vector<Point> FindPointsArround(Quad q);

    QuadTree *q1 = nullptr;
    QuadTree *q2 = nullptr;
    QuadTree *q3 = nullptr;
    QuadTree *q4 = nullptr;

    Quad quad;

    QuadTree *parent = nullptr;
private:
    static const int POINT_COUNT = 1;
    std::vector<Point> points;
    bool filled = false;
};

#endif // QUADTREE_H