// praktika.cpp: ���������� ����� ����� ��� ����������� ����������.
//


#include "stdafx.h"
#include <iostream>
#include <fstream> // ������ � �������
#include <iomanip> // ������������ �����/������
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

	char buff[50]; // ����� �������������� �������� ������������ �� ����� ������
	ifstream fin("C:\\Users\\������\\Desktop\\11.txt"); // ������� ���� ��� ������

		int n = 0;

		while (!fin.eof())
		{
					fin >> buff; // ������� ������ ����� �� �����
					float ftemp = atof(buff);
					p[n].x = ftemp;
					cout << p[n].x;

					fin >> buff; // ������� ������ ����� �� �����
					float ftemp2 = atof(buff);
					p[n].y = ftemp2;
					cout << ' ' << p[n].y;

					fin >> buff; // ������� ������ ����� �� �����
					p[n].text = buff;
					cout << ' ' << p[n].text << endl;
					n++;
		}
	system("pause");
	return 0;
}

