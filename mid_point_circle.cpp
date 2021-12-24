#include <iostream>
#include <graphics.h>
#include <dos.h>   //for delay()
#include <conio.h> //for getch()
using namespace std;

int xCentre, yCentre;
int color = 15; //default white
void plotPoints(int x, int y)
{
    putpixel(x + xCentre, y + yCentre, color);
    putpixel(y + xCentre, x + yCentre, color);
    putpixel(y + xCentre, -x + yCentre, color);
    putpixel(x + xCentre, -y + yCentre, color);
    putpixel(-x + xCentre, -y + yCentre, color);
    putpixel(-y + xCentre, -x + yCentre, color);
    putpixel(-y + xCentre, x + yCentre, color);
    putpixel(-x + xCentre, y + yCentre, color);
}
void circleMidPoint(int xC, int yC, int r)
{
    xCentre = xC;
    yCentre = yC;
    int x = 0, y = r;
    float Pk = 1.25 - r;
    int k = 0;
    for (; x <= y; k++)
    {
        color = (k % 16) + 1;
        plotPoints(x, y);
        x++;
        if (Pk < 0)
        {
            y = y;
            Pk = Pk + 2 * (x) + 1;
        }
        else
        {
            y = y - 1;
            Pk = Pk + 2 * (x)-2 * (y);
        }
    }
}
int main()
{
    initwindow(960, 960); //width, height
    int xC, yC, r;
    cout << "Enter center as x1, y1 and radius of the circle\n";
    cin >> xC >> yC >> r;
    circleMidPoint(xC, yC, r);
    getch();
    closegraph();
}

// Sample input
// 200 200 50