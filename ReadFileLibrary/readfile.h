#ifndef READFILE_H
#define READFILE_H
#include <fstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>


class ReadFile
{

public:
    ReadFile();
    vector<Point> reading(string Filename);


};

#endif // READFILE_H
