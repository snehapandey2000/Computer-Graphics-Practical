#include <iostream>
#include <cmath>
#include <graphics.h>
#include <dos.h>   //for delay()
#include <conio.h> //for getch()
using namespace std;
#define PI 3.141592653589793238

int w, h; //width, height of black screen
int xNewOrigin, yNewOrigin;

inline float xNew(float x)
{
    return x + xNewOrigin;
}
inline float yNew(float y)
{
    return -y + yNewOrigin;
}

int main()
{
    w = 1500, h = 900;
    initwindow(w, h); //width, height

    //making axes
    line(w / 2, 0, w / 2, h);
    line(0, h / 2, w, h / 2);

    xNewOrigin = w / 2;
    yNewOrigin = h / 2;

    /*Your code here*/
    //whenever sending any point (x1,y1) to ANY function,
    //write xNew(x1) in place of x1
    //write yNew(y1) in place of y1
    //(xNew(),yNew(),xNew(),yNew())
    //whwnever you clear screen using cleardevice(), then again make the axes
    //cleardevice();
    //line(w/2,0,w/2,h);
    //line(0,h/2,w,h/2);

    line(xNew(0), yNew(0), xNew(100), yNew(100));
    circle(xNew(0), yNew(0), 100);

    getch();
    closegraph();
}