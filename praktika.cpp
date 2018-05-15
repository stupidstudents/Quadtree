// praktika.cpp: определяет точку входа для консольного приложения.
//


#include "stdafx.h"
#include <iostream>
#include <fstream> // работа с файлами
#include <iomanip> // манипуляторы ввода/вывода
using namespace std;

struct Point
{
	float x;
	float y;
	char *text;

};

int b = 0;
Point *p = new Point[b];

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");

	char buff[50]; // буфер промежуточного хранения считываемого из файла текста
	ifstream fin("C:\\Users\\Андрей\\Desktop\\11.txt"); // открыли файл для чтения

		int n = 0;

		while (!fin.eof())
		{
					fin >> buff; // считали первое слово из файла
					float ftemp = atof(buff);
					p[n].x = ftemp;
					cout << p[n].x;

					fin >> buff; // считали первое слово из файла
					float ftemp2 = atof(buff);
					p[n].y = ftemp2;
					cout << ' ' << p[n].y;

					fin >> buff; // считали первое слово из файла
					p[n].text = buff;
					cout << ' ' << p[n].text << endl;
					n++;
		}
	system("pause");
	return 0;
}

