
#include "readfile.h"

using namespace std;

struct Point{
    double x;
    double y;
    string Inf;
};

ReadFile::ReadFile()
{

}


vector<Point> ReadFile::reading(string Filename){
   vector<Point>points;
   Point p;
   string str;
   char buff[50];
   char * ptrEnd = NULL;
   ifstream fin;
   fin.open(Filename);
    if(fin){
            while(!fin.eof()){


                fin >> buff;
                p.x = strtod(buff, &ptrEnd);
                if(*ptrEnd != '\0')
                    cout<< "Ошибка формата ввода";
                fin >> buff;
                p.y = strtod(buff, &ptrEnd);
                if(*ptrEnd != '\0')
                    cout<< "Ошибка формата ввода";
                getline(fin, str);
                p.Inf = str;
                points.push_back(p);
            }
            fin.close();
    }
    else
        cout<<"file was not opened";
    return points;

}

