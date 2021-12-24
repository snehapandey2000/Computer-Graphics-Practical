#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

void drawBresenhmaLine(int x1, int y1, int x2, int y2)
{

    int dx = x2 - x1;
    int dy = y2 - y1;
    float m = (float)dy / dx; //slope
    cout << "Slope= " << m << "\n";

    int mod_dx = abs(dx), mod_dy = abs(dy);
    int p0;
    int xChange, yChange;
    //drawing pixels
    int x = x1, y = y1, pk;
    putpixel(x, y, WHITE);
    delay(5);

    if (abs(m) <= 1)
    {
        //along x axis 1 unit change
        xChange = dx / mod_dx;

        //calculate p knot
        p0 = (2 * mod_dy) - mod_dx;

        pk = p0;
        for (int k = 1; k <= mod_dx; k++)
        {

            x = x + xChange;

            if (pk < 0)
            {
                yChange = 0;
                pk = pk + 2 * mod_dy;
            }
            else
            {
                yChange = dy / mod_dy;
                pk = pk + 2 * mod_dy - 2 * mod_dx;
            }
            y = y + yChange;
            cout << x << " , " << y << "\n";
            putpixel(x, y, (k % 16));
            delay(5);
        }
    }
    else
    {
        //along y axis 1 unit change
        yChange = dy / mod_dy;
        p0 = (2 * mod_dx) - mod_dy;

        pk = p0;
        for (int k = 1; k <= mod_dy; k++)
        {

            y = y + yChange;

            if (pk < 0)
            {
                xChange = 0;
                pk = pk + 2 * mod_dx;
            }
            else
            {
                xChange = dx / mod_dx;
                pk = pk + 2 * mod_dx - 2 * mod_dy;
            }
            x = x + xChange;
            cout << x << " , " << y << "\n";
            putpixel(x, y, (k % 16));
            delay(5);
        }
    }
}

int main()
{
    initwindow(960, 960); //width, height
    int x1, y1, x2, y2;
    int n;
    cout << "Enter the number of lines you want to plot"
         << "\n";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter  the two points x1, y1 and x2, y2"
             << "\n";
        cin >> x1 >> y1 >> x2 >> y2;
        drawBresenhamLine(x1, y1, x2, y2);
    }

    getch();
    closegraph();
}

// Sample Input
// 1
// 100 100 200 50
