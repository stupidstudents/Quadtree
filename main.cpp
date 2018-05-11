#include <time.h>
#include <cstdlib>
#include <quadtree.h>

using namespace std;

Point MakeRndPoint();

int main()
{
    srand(time(0));

    QuadTree *quadTree = new QuadTree(nullptr, 0, 0, 500);

    //Create some random points and insert it
    /*for (size_t i = 0; i < 500; i++) {
        quadTree->Insert(MakeRndPoint());
    }*/

    Point p1 = {0, 500};
    Point p2 = {50, 50};
    Point p3 = {100, 100};
    Point p4 = {400, 400};

    printf("---Insert result: %d\n", quadTree->Insert(p1));
    printf("---Insert result: %d\n", quadTree->Insert(p2));
    printf("---Insert result: %d\n", quadTree->Insert(p3));
    printf("---Insert result: %d\n", quadTree->Insert(p4));

    //Finding points arround sector
    Quad fQuad = {0, 0, 61};
    vector<Point> fPnt = quadTree->FindPointsArround(fQuad);

    if (fPnt.size() > 0) {
        for (size_t i = 0; i < fPnt.size(); i++) {
            printf("P[%d]: X-%f, Y-%f\n", i, fPnt[i].X, fPnt[i].Y);
        }
    }
    else printf("P: NOT FOUND\n");

    delete quadTree;

    return 0;
}

Point MakeRndPoint() {
    Point p;
    p.X = rand() % 450 + 10;
    p.Y = rand() % 450 + 10;

    return p;
}
