#include <iostream>
#include <dos.h>   //for delay()
#include <conio.h> //for getch()
#include <cmath>   //for abs()
#include <graphics.h>
using namespace std;

int xCentre, yCentre;

void plotPoints(int x, int y)
{
    putpixel(x + xCentre, y + yCentre, YELLOW);
    putpixel(y + xCentre, x + yCentre, YELLOW);
    putpixel(y + xCentre, -x + yCentre, YELLOW);
    putpixel(x + xCentre, -y + yCentre, YELLOW);
    putpixel(-x + xCentre, -y + yCentre, YELLOW);
    putpixel(-y + xCentre, -x + yCentre, YELLOW);
    putpixel(-y + xCentre, x + yCentre, YELLOW);
    putpixel(-x + xCentre, y + yCentre, YELLOW);
    delay(20);
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
    cout << "Enter center as x,y and radius of the circle\n";
    cin >> xC >> yC >> r;
    circleBresenham(xC, yC, r);

    //circleBresenham(300,400,200);
    getch();
    closegraph();
}

// Sample input
// 200 200 50
