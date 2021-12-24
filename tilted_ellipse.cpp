#include <iostream>
using namespace std;
#include <graphics.h>
#include <conio.h> //for getch
#include <dos.h>   //for delay
#include <cmath>
#define PI 3.141592653589793238

int color = 15; //default white
int xCentre, yCentre;
float alpha; //in radian from x axis, ACW
float sinAlpha;
float cosAlpha;

int rotateX(int x, int y)
{
    return (x * cosAlpha - y * sinAlpha);
}
int rotateY(int x, int y)
{
    return (y * cosAlpha + x * sinAlpha);
}

void plotPoints(int x, int y)
{
    //(x,y)
    putpixel(rotateX(x, y) + xCentre, rotateY(x, y) + yCentre, color);
    //x,-y
    putpixel(rotateX(x, -y) + xCentre, rotateY(x, -y) + yCentre, color);
    //-x,-y
    putpixel(rotateX(-x, -y) + xCentre, rotateY(-x, -y) + yCentre, color);
    //-x,y
    putpixel(rotateX(-x, y) + xCentre, rotateY(-x, y) + yCentre, color);
    // delay(1);
}
void ellipseMidPoint(int xC, int yC, int rx, int ry, float _alpha)
{ //angle in radian

    xCentre = xC;
    yCentre = yC;

    alpha = _alpha;
    sinAlpha = sin(alpha);
    cosAlpha = cos(alpha);
    //no cases acc to rx and ry
    int rySquare = ry * ry;
    int rxSquare = rx * rx;
    int x = 0, y = ry;

    float P1k = (rySquare) - (rxSquare * ry) + (0.25 * rxSquare);

    for (; (2 * rySquare * x) < (2 * rxSquare * y);)
    {
        plotPoints(x, y);
        x = x + 1;
        if (P1k < 0)
        {
            y = y;
            P1k = P1k + (2 * rySquare * x) + rySquare;
        }
        else
        {
            y = y - 1;
            P1k = P1k + (2 * rySquare * x) + rySquare - (2 * rxSquare * y);
        }
    }

    float P2k = rySquare * (x + 0.5) * (x + 0.5) + rxSquare * (y - 1) * (y - 1) - rxSquare * rySquare;
    for (; y >= 0;)
    {
        plotPoints(x, y);
        y = y - 1;
        if (P2k > 0)
        {
            x = x;
            P2k = P2k - (2 * rxSquare * y) + rxSquare;
        }
        else
        {
            x = x + 1;
            P2k = P2k - (2 * rxSquare * y) + rxSquare + (2 * rySquare * x);
        }
    }
}
int main()
{
    initwindow(1000, 1000);

    int xC, yC, rx, ry;
    float _alpha;
    bool drawAgain = true;
    ellipseMidPoint(400, 400, 200, 100, 0);
    ellipseMidPoint(400, 400, 200, 100, PI / 4);
    ellipseMidPoint(400, 400, 200, 100, PI / 2);
    ellipseMidPoint(400, 400, 200, 100, 3 * PI / 4);
    getch();
    closegraph();
}
