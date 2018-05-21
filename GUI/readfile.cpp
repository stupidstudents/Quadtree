#include "readfile.h"

using namespace std;

int ReadFile::reading(string Filename, vector<Point*> *points){
   string str;
   char buff[50];
   char * ptrEnd = NULL;
   ifstream fin;
   fin.open(Filename);

   if(fin){
            while(!fin.eof()){
                Point *p = new Point();

                fin >> buff;
                p->X = strtod(buff, &ptrEnd);
                if(*ptrEnd != '\0')
                    return -2; //data error
                fin >> buff;
                p->Y = strtod(buff, &ptrEnd);
                if(*ptrEnd != '\0')
                    return -2; //data error
                getline(fin, str);
                p->text = str;
                p->clicked = false;
                points->push_back(p);
            }
            fin.close();
    }
    else
        return -1; //file wasn't open
    return 1;

}

