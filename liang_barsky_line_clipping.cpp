#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;

int xNewOrigin, yNewOrigin;

float xNew(float x)
{
    return x + xNewOrigin;
}
float yNew(float y)
{
    return -y + yNewOrigin;
}

float xmin, xmax, ymin, ymax;
class lines
{
public:
    float x1, y1, x2, y2;
};

void clipLiangBarskey(lines currLine)
{
    cout << "Points of given line are ( " << currLine.x1 << " , " << currLine.y1 << " ) and ( " << currLine.x2 << " , " << currLine.y2 << " )\n";
    float dx = currLine.x2 - currLine.x1;
    float dy = currLine.y2 - currLine.y1;
    cout << "dx: " << dx << "\ndy: " << dy << "\n";
    float p[5], q[5];
    p[1] = -dx;
    q[1] = currLine.x1 - xmin;
    p[2] = dx;
    q[2] = xmax - currLine.x1;
    p[3] = -dy;
    q[3] = currLine.y1 - ymin;
    p[4] = dy;
    q[4] = ymax - currLine.y1;

    cout << "p1 = " << p[1] << "   and    "
         << "q1 = " << q[1] << "\n";
    cout << "p2 = " << p[2] << "   and    "
         << "q2 = " << q[2] << "\n";
    cout << "p3 = " << p[3] << "   and    "
         << "q3 = " << q[3] << "\n";
    cout << "p4 = " << p[4] << "   and    "
         << "q4 = " << q[4] << "\n";

    if (p[1] == 0)
    {
        cout << "Line parallel to VERTICAL boundary\n";
        if (q[1] < 0 || q[2] < 0)
        {
            if (q[1] < 0)
            {
                cout << "Line completely outside of window on LEFT side.";
            }
            else
            {
                cout << "Line completely outside of window on RIGHT side.";
            }
            cout << "So NO need of clipping.\n";
            return;
        }
    }

    if (p[3] == 0)
    {
        cout << "Line parallel to HORIZONTAL boundary\n";
        if (q[3] < 0 || q[4] < 0)
        {
            if (q[3] < 0)
            {
                cout << "Line completely outside of window at BOTTOM.";
            }
            else
            {
                cout << "Line completely outside of window at TOP.";
            }
            cout << "So NO need of clipping.\n";
            return;
        }
    }
    cout << "\n";
    float u1, u2;
    float xi1, yi1, xi2, yi2;
    if (p[1] < 0 || p[2] < 0 || p[3] < 0 || p[4] < 0)
    {
        vector<float> tempVector;
        tempVector.push_back(0);
        for (int i = 1; i < 5; i++)
        {
            if (p[i] < 0)
            {
                tempVector.push_back(q[i] / p[i]);
            }
        }
        float max = INT_MIN;
        cout << "u1 = max( ";
        for (int i = 0; i < tempVector.size(); i++)
        {
            if (tempVector[i] > max)
            {
                max = tempVector[i];
            }
            cout << tempVector[i] << " , ";
        }
        cout << " )\n";
        u1 = max;
        cout << "u1 = " << u1 << "\n";

        xi1 = currLine.x1 + (u1 * dx);
        yi1 = currLine.y1 + (u1 * dy);

        if (u1 == 0)
        {
            cout << "As u1=0, i.e the starting point ( " << currLine.x1 << " , " << currLine.y1 << " ) lies ON or INSIDE the window, so NO clipping on this side.\n";
        }
        else
        {
            cout << "As u1!=0,  clipping required on this side.\n";

            cout << "Intersection point with window";
            if (xi1 == xmin)
            {
                cout << "(xmin)";
            }
            if (xi1 == xmax)
            {
                cout << "(xmax)";
            }
            if (yi1 == ymin)
            {
                cout << "(ymin)";
            }
            if (yi1 == ymax)
            {
                cout << "(ymax)";
            }

            cout << " : ( " << xi1 << " , " << yi1 << " )\n";
        }
    }
    cout << "\n";
    //sytep 3
    if (p[1] > 0 || p[2] > 0 || p[3] > 0 || p[4] > 0)
    {
        vector<float> tempVector;
        tempVector.push_back(1);

        for (int i = 1; i < 5; i++)
        {
            if (p[i] > 0)
            {
                tempVector.push_back(q[i] / p[i]);
            }
        }
        float min = INT_MAX;
        cout << "u2 = min( ";
        for (int i = 0; i < tempVector.size(); i++)
        {
            if (tempVector[i] < min)
            {
                min = tempVector[i];
            }
            cout << tempVector[i] << " , ";
        }
        cout << " )\n";
        u2 = min;
        cout << "u2 = " << u2 << "\n";

        if (u1 > u2)
        {
            cout << "As u1>u2 so Line is completely outside .Eliminate it\n"; //?check
            return;
        }

        xi2 = currLine.x1 + (u2 * dx);
        yi2 = currLine.y1 + (u2 * dy);

        if (u2 == 1)
        {
            cout << "As u2=1, i.e the ending point ( " << currLine.x2 << " , " << currLine.y2 << " ) lies ON or INSIDE the window, so NO clipping on this side.\n";
        }
        else
        {
            cout << "As u2!=1,  clipping required on this side.\n";

            cout << "Intersection point with window";
            if (xi2 == xmin)
            {
                cout << "(xmin)";
            }
            if (xi2 == xmax)
            {
                cout << "(xmax)";
            }
            if (yi2 == ymin)
            {
                cout << "(ymin)";
            }
            if (yi2 == ymax)
            {
                cout << "(ymax)";
            }

            cout << " : ( " << xi2 << " , " << yi2 << " )\n";
        }
    }

    cout << "So the final clipped line has coordinates are ( " << xi1 << " , " << yi1 << " ) and ( " << xi2 << " , " << yi2 << " )\n";
    setcolor(YELLOW);
    line(xNew(xi1), yNew(yi1), xNew(xi2), yNew(yi2));
    return;
}

int main()
{
    cout << "Enter window coordinates xmin, xmax, ymin, ymax\n";
    cin >> xmin >> xmax >> ymin >> ymax;
    int w, h;
    w = 1500, h = 900;
    initwindow(w, h);

    //making axes
    line(w / 2, 0, w / 2, h);
    line(0, h / 2, w, h / 2);

    xNewOrigin = w / 2;
    yNewOrigin = h / 2;

    // Drawing Window using Lines
    line(xNew(xmin), yNew(ymin), xNew(xmax), yNew(ymin));
    line(xNew(xmax), yNew(ymin), xNew(xmax), yNew(ymax));
    line(xNew(xmax), yNew(ymax), xNew(xmin), yNew(ymax));
    line(xNew(xmin), yNew(ymax), xNew(xmin), yNew(ymin));

    cout << "Number of lines you want to plot\n";
    int n;
    cin >> n;
    vector<lines> linesVector;
    cout << "Enter x1, y1, x2, y2 for each line.\n";
    for (int i = 0; i < n; i++)
    {
        lines tempLine;
        cin >> tempLine.x1 >> tempLine.y1 >> tempLine.x2 >> tempLine.y2;
        line(xNew(tempLine.x1), yNew(tempLine.y1), xNew(tempLine.x2), yNew(tempLine.y2));
        linesVector.push_back(tempLine);
    }
    cout << "Intersection points for the line\n\n";
    for (int i = 0; i < n; i++)
    {
        cout << "For " << (i + 1) << " th line\n";
        //line(xNew(linesVector[i].x1),yNew(linesVector[i].y1),xNew(linesVector[i].x2), yNew(linesVector[i].y2));
        clipLiangBarskey(linesVector[i]);
        cout << "\n--------------------------------------------------\n";
    }
    getch();
    closegraph();
    return 0;
}

/*
Enter xmin, xmax, ymin, ymax
-300 200 -200 300

How many lines?
5

Enter x1, y1, x2, y2
-400 200 -100 400
-100 350 300 350
-200 300 100 200
100 -200 300 300
-400 400 -200 100
*/
