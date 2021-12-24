#include <iostream>
#include <graphics.h>
#include <stdio.h>
#include <cmath>
using namespace std;

void ddaLine(float x1, float y1, float x2, float y2)
{

	float dx = x2 - x1;
	float dy = y2 - y1;
	float m = dy / dx;

	float increment;

	if (abs(m) <= 1)
	{
		//along x axis 1 unit change
		increment = abs(dx);
	}
	else
	{
		//along y axis 1 unit change
		increment = abs(dy);
	}

	float xdiff = dx / increment;
	float ydiff = dy / increment;

	//drawing pixels
	float x = x1, y = y1;

	putpixel(round(x), round(y), YELLOW);
	for (int k = 1; k <= increment; k++)
	{
		x = x + xdiff;
		y = y + ydiff;
		putpixel(round(x), round(y), YELLOW);
	}
}

int main()
{
	initwindow(960, 960); //width, height

	float x1, y1, x2, y2;
	int n;
	cout << "Enter the number of lines you want to plot"
		 << "\n";
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter the two points x1, y1 and x2, y2"
			 << "\n";
		cin >> x1 >> y1 >> x2 >> y2;
		ddaLine(x1, y1, x2, y2);
	}

	getch();
	closegraph();
}

// Sample Input
// 1
// 100 100 200 50
