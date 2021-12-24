#include <iostream>
#include <graphics.h>
#include <dos.h>   //for delay()
#include <conio.h> //for getch()
#include <cmath>   //for abs()
using namespace std;

int xCentre, yCentre, i = 0;
int color[] = {11, 3, 9, 13, 5, 14, 1, 2, 11, 3, 9, 5, 10, 12, 13, 12, 3, 5, 6, 11, 0};

void plotPoints(int x, int y)
{
    putpixel(x + xCentre, y + yCentre, color[i]);
    putpixel(y + xCentre, x + yCentre, color[i]);
    putpixel(y + xCentre, -x + yCentre, color[i]);
    putpixel(x + xCentre, -y + yCentre, color[i]);
    putpixel(-x + xCentre, -y + yCentre, color[i]);
    putpixel(-y + xCentre, -x + yCentre, color[i]);
    putpixel(-y + xCentre, x + yCentre, color[i]);
    putpixel(-x + xCentre, y + yCentre, color[i]);
    delay(0.5);
}

void circleBresenham(int xC, int yC, int r)
{

    xCentre = xC;
    yCentre = yC;

    int x = 0, y = r;
    int Dk = 3 - (2 * r);

    for (; x <= y; x++)
    {

        plotPoints(x, y);
        if (Dk < 0)
        {
            y = y;
            Dk = Dk + (4 * x) + 6;
        }
        else
        {
            y = y - 1;
            Dk = Dk + 4 * (x - y) + 10;
        }
    }
}
int main()
{
    initwindow(960, 960); //width, height

    int xC, yC, r;
    xC = 375;
    yC = 300;
    r = 5;
    for (int j = 0; j < 8; j++)
    {
        while (r <= 100)
        {
            circleBresenham(xC, yC, r);
            circleBresenham(100, 100, r);
            circleBresenham(650, 100, r);
            circleBresenham(100, 500, r);
            circleBresenham(650, 500, r);
            i++;
            r += 5;
        }
        while (r >= 5)
        {
            circleBresenham(xC, yC, r);
            circleBresenham(100, 100, r);
            circleBresenham(650, 100, r);
            circleBresenham(100, 500, r);
            circleBresenham(650, 500, r);
            r -= 5;
        }
    }
    getch();
    closegraph();
}
