#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <stdio.h>
#include <string>

#define INSERT_FAIL -1
#define INSERT_SUCCESS 0
#define QUAD_BORDER_INTERSECT 1
#define QUAD_CONTAIN 2
#define QUAD_NOT_CONTAIN 3

struct Point {
    double X;
    double Y;

    std::string text;
    bool clicked;
};

struct Quad {
    Point p;
    double size;

    int ContainPoint(Point *p);
    bool IntersectWithQuad(Quad q);
};

class QuadTree
{
public:
    QuadTree(QuadTree *parent, Quad quad);
    QuadTree(QuadTree *parent, double X, double Y, double size);
    ~QuadTree();

    int Insert(Point *p);
    void Divide();

    Quad MakeQuad(double X, double Y, double size);
    Point MakePoint(double X, double Y, std::string text = "");

    std::vector<Point*> FindPointsArround(Quad q);

    Quad quad;

    QuadTree *q1 = 0;
    QuadTree *q2 = 0;
    QuadTree *q3 = 0;
    QuadTree *q4 = 0;

    QuadTree *parent = 0;

    std::vector<Point*> points;
private:
    static const int POINT_COUNT = 1;
    bool filled = false;
};

#endif // QUADTREE_H
