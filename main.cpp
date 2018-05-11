#include <stdio.h>
#include <quadtree.h>

#include <time.h>
#include <cstdlib>

int main()
{
    srand(time(0));

    Quad treeQuad = {0, 0, 500};
    QuadTree *quadTree = new QuadTree(nullptr, treeQuad);

    /*for (size_t i = 0; i < 500; i++) {
        p.X = rand() % 450 + 10;
        p.Y = rand() % 450 + 10;

        printf("Try to insert point %d: X-%f, Y-%f\n", i, p.X, p.Y);
        t->Insert(p);
    }*/

    Point p;

    p.X = 48; p.Y = 61;
    quadTree->Insert(p);

    p.X = 113; p.Y = 94;
    quadTree->Insert(p);

    p.X = 427; p.Y = 103;
    quadTree->Insert(p);

    p.X = 435; p.Y = 102;
    quadTree->Insert(p);

    p.X = 389; p.Y = 110;
    quadTree->Insert(p);

    Quad fQuad = {10, 10, 200};
    std::vector<Point> fPnt = quadTree->FindPointsArround(fQuad);

    if (fPnt.size() > 0)
        for (size_t i = 0; i < fPnt.size(); i++) {
            printf("P[%d]: X-%f, Y-%f\n", i, fPnt[i].X, fPnt[i].Y);
        }
    else printf("P: NOT FOUND\n");

    delete quadTree;

    return 0;
}
