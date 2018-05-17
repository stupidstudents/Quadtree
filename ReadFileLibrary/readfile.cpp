
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


void ReadFile::reading(){
   vector<Point>points;
   Point p;
   setlocale(LC_ALL, "rus");
   string str;
   ifstream fin;
   int i=0;
   fin.open("data.txt");
    if(fin){
            while(!fin.eof()){
                points.push_back(p);
                fin >> points.at(i).x;
                fin >> points.at(i).y;
                getline(fin, str);
                points.at(i).Inf = str;
                i++;
            }
            fin.close();
    }
    else
        cout<<"file was not opened";
    for(vector<Point>::iterator it = points.begin(); it!=points.end();it++){
        cout<<it->x<<" "<<it->y<<" "<<it->Inf<<endl;
    }
}

