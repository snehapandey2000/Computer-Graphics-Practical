#include <graphics.h>
#include <stdlib.h>
#include <iostream>
#include <conio.h>
using namespace std;

void displayp1(int xc, int yc, int x, int y, int c)
{

	putpixel(xc + x, yc + y, c);
	putpixel(xc + x, yc - y, c);
	putpixel(xc - x, yc + y, c);
	putpixel(xc - x, yc - y, c);
	putpixel(xc + x, yc + y, c);
	putpixel(xc + x, yc - y, c);
	putpixel(xc - x, yc + y, c);
	putpixel(xc - x, yc - y, c);
}

int main()
{
	int xc, yc, x, y;
	float p;
	long rx, ry;
	initwindow(960, 960);
	cout << "\n\n";

	cout << "\t\tEnter Coordinates of Centre for the ellipse : ";
	cin >> xc >> yc;
	cout << "\t\tEnter X,Y axis length of Ellipse: ";
	cin >> rx >> ry;

	p = ry * ry - rx * rx * ry + rx * rx / 4;
	x = 0;
	y = ry;
	while (2.0 * ry * ry * x <= 2.0 * rx * rx * y)
	{
		if (p < 0)
		{
			x++;
			p = p + 2 * ry * ry * x + ry * ry;
		}
		else
		{
			x++;
			y--;
			p = p + 2 * ry * ry * x - 2 * rx * rx * y - ry * ry;
		}
		displayp1(xc, yc, x, y, 15);
	}

	p = ry * ry * (x + 0.5) * (x + 0.5) + (rx * rx * (y - 1) * (y - 1)) - (rx * rx * ry * ry);
	while (y > 0)
	{
		if (p <= 0)
		{
			x++;
			y--;
			p = p + 2 * ry * ry * x - 2 * rx * rx * y + rx * rx;
		}
		else
		{
			y--;
			p = p - 2 * rx * rx * y + rx * rx;
		}
		displayp1(xc, yc, x, y, 15);
	}

	getch();
	closegraph();
	return 0;
}

// Sample Input
// 300 300
// 100 50
