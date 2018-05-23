#ifndef READFILE_H
#define READFILE_H
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <stdlib.h> 
#include "quadtree.h"


class ReadFile
{

public:
    int reading(std::string Filename, std::vector<Point*> *points);
};

#endif // READFILE_H
