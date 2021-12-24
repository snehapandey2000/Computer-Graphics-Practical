#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;

// Global Variables
float xmin, xmax, ymin, ymax;

// Lines where co-ordinates are (x1, y1) and (x2, y2)
class lines
{
public:
    float x1, y1, x2, y2;
};

// This will return the sign required.
int sign(float difference)
{
    if (difference > 0)
        return 1;
    else
        return 0;
}

float currentPointX, currentPointY;
int top()
{
    return (sign(currentPointY - ymax));
}
int bottom()
{
    return (sign(ymin - currentPointY));
}
int right()
{
    return (sign(currentPointX - xmax));
}
int left()
{
    return (sign(xmin - currentPointX));
}

string arrayToString(int a[])
{
    string ans = "";
    for (int i = 0; i < 4; i++)
    {

        if (a[i] == 0)
            ans += '0';
        else
            ans += '1';
    }
    return ans;
}

float m, c;
float YFromX(float x)
{
    return (m * x + c);
}
float XFromY(float y)
{
    return ((y - c) / m);
}

string logicalAND_OfStrings(string b1, string b2)
{
    string ans = "";
    for (int i = 0; i < 4; i++)
    {
        int val = ((b1[i] - '0') & (b2[i] - '0'));
        if (val == 0)
            ans += '0';
        else
            ans += '1';
    }
    return ans;
}
// CohenSutherLand LineClipping Algorithm
// This will clip the lines as per window boundries.
void clip(lines currentLine)
{
    // finding slope of line y=mx+c as (y-y1)=m(x-x1)+c
    // where m is slope m=dy/dx;

    m = (currentLine.y2 - currentLine.y1) / (float)(currentLine.x2 - currentLine.x1);
    c = currentLine.y1 - m * currentLine.x1;
    // arrays will store bits
    // Here bits impiles bitsFirstPoint_String Point whereas bitsSecondPoint implies bitsSecondPoint_String point
    int bitsFirstPoint[4], bitsSecondPoint[4];

    // setting color of graphics to be RED
    setcolor(RED);

    // Finding Bits
    currentPointX = currentLine.x1;
    currentPointY = currentLine.y1;
    bitsFirstPoint[0] = top();
    bitsFirstPoint[1] = bottom();
    bitsFirstPoint[2] = right();
    bitsFirstPoint[3] = left();

    currentPointX = currentLine.x2;
    currentPointY = currentLine.y2;
    bitsSecondPoint[0] = top();
    bitsSecondPoint[1] = bottom();
    bitsSecondPoint[2] = right();
    bitsSecondPoint[3] = left();

    // bitsFirstPoint_String will used for bitsFirstPoint_String coordinates and bitsSecondPoint_String for final
    string logicalAND = "";
    string bitsFirstPoint_String = arrayToString(bitsFirstPoint);
    string bitsSecondPoint_String = arrayToString(bitsSecondPoint);

    cout << "Initial Points of line:( " << currentLine.x1 << " , " << currentLine.y1 << " ) [ " << bitsFirstPoint_String << " ] and ( " << currentLine.x2 << " , " << currentLine.y2 << " ) [ " << bitsSecondPoint_String << " ]\n";

    // if both points are inside the Accept the line and draw
    if (bitsFirstPoint_String == bitsSecondPoint_String && bitsSecondPoint_String == "0000")
    {
        // inbuild function to draw the line from(x1, y1) to (x2, y2)
        cout << "Visible line, NO need of clipping\n";
        line(currentLine.x1, currentLine.y1, currentLine.x2, currentLine.y2);
        return;
    }
    // this will contain cases where line maybe totally outside for partially inside
    else
    {
        // taking bitwise and of every value
        logicalAND = logicalAND_OfStrings(bitsFirstPoint_String, bitsSecondPoint_String);

        // as per algo if AND is not 0000 means line is completely outside hene draw nothing and retrurn
        if (logicalAND != "0000")
        {
            cout << "NOT Visible line, No need of clipping\n";
            return;
        }
        else
        {
            cout << "Clipping candidate line\n";
        }

        // Here contain cases of partial inside or outside
        // So check for every boundary one by one
        string startingPoint;

        // float startingPointX, startingPointY;

        while (true)
        {

            if (bitsFirstPoint_String == "0000")
            {
                startingPoint = "second";
            }
            else
            { //captures both cases when send point is 0000 or none of the point is 0000
                startingPoint = "first";
            }
            if (startingPoint == "first")
            {
                int i;
                for (i = 0; i < 4; i++)
                {
                    if (bitsFirstPoint[i] == 1)
                    {
                        break;
                    }
                }
                float xi, yi;
                string intersectionWith;
                if (i == 0)
                {
                    yi = ymax;
                    xi = XFromY(ymax);
                    intersectionWith = "ymax";
                }
                else if (i == 1)
                {
                    yi = ymin;
                    xi = XFromY(ymin);
                    intersectionWith = "ymin";
                }
                else if (i == 2)
                {
                    xi = xmax;
                    yi = YFromX(xmax);
                    intersectionWith = "xmax";
                }
                else if (i == 3)
                {
                    xi = xmin;
                    yi = YFromX(xmin);
                    intersectionWith = "xmin";
                }

                cout << "Intersection point with window (with " << intersectionWith << ") : ( " << xi << " , " << yi << " )";
                currentLine.x1 = xi;
                currentLine.y1 = yi;

                currentPointX = currentLine.x1;
                currentPointY = currentLine.y1;
                bitsFirstPoint[0] = top();
                bitsFirstPoint[1] = bottom();
                bitsFirstPoint[2] = right();
                bitsFirstPoint[3] = left();

                bitsFirstPoint_String = arrayToString(bitsFirstPoint);
                cout << "[ " << bitsFirstPoint_String << " ]\n";
            }
            else if (startingPoint == "second")
            {
                int i;
                for (i = 0; i < 4; i++)
                {
                    if (bitsSecondPoint[i] == 1)
                    {
                        break;
                    }
                }
                float xi, yi;
                string intersectionWith;
                if (i == 0)
                {
                    yi = ymax;
                    xi = XFromY(ymax);
                    intersectionWith = "ymax";
                }
                else if (i == 1)
                {
                    yi = ymin;
                    xi = XFromY(ymin);
                    intersectionWith = "ymin";
                }
                else if (i == 2)
                {
                    xi = xmax;
                    yi = YFromX(xmax);
                    intersectionWith = "xmax";
                }
                else if (i == 3)
                {
                    xi = xmin;
                    yi = YFromX(xmin);
                    intersectionWith = "xmin";
                }

                cout << "Intersection point with window (with " << intersectionWith << ") : ( " << xi << " , " << yi << " )";

                currentLine.x2 = xi;
                currentLine.y2 = yi;

                currentPointX = currentLine.x2;
                currentPointY = currentLine.y2;

                bitsSecondPoint[0] = top();
                bitsSecondPoint[1] = bottom();
                bitsSecondPoint[2] = right();
                bitsSecondPoint[3] = left();

                bitsSecondPoint_String = arrayToString(bitsSecondPoint);
                cout << "[ " << bitsSecondPoint_String << " ]\n";
            }

            cout << "Updated end points (first and second): (" << currentLine.x1 << " , " << currentLine.y1 << " ) [ " << bitsFirstPoint_String << " ] and ( " << currentLine.x2 << " , " << currentLine.y2 << " ) [ " << bitsSecondPoint_String << " ]\n";

            if (bitsFirstPoint_String == "0000" && bitsSecondPoint_String == "0000")
            {
                cout << "This updated part of line COMPLETELY INSIDE the window i.e. VISIBLE line, so clipping completed\n";
                return;
            }
            else
            {
                if (logicalAND_OfStrings(bitsFirstPoint_String, bitsSecondPoint_String) != "0000")
                {
                    cout << "This updated part of line is NOT VISIBLE line, hence its outside so of no concern, so algo stop here.\n";
                    return;
                }
                else
                {
                    cout << "This updated part of line is still CLIPPING CANDIDATE line, so continue clipping\n";
                    continue;
                }
            }
            cout << "\n";
        }
        //end of loop
    }
}

// Driver Function
int main()
{
    // int gd = DETECT, gm;

    // Setting values of Clipping window
    cout << "Enter xmin, xmax, ymin, ymax\n";
    cin >> xmin >> xmax >> ymin >> ymax;

    // intialize the graph
    initwindow(500, 500);

    // Drawing Window using Lines
    line(xmin, ymin, xmax, ymin);
    line(xmax, ymin, xmax, ymax);
    line(xmax, ymax, xmin, ymax);
    line(xmin, ymax, xmin, ymin);

    cout << "How many lines?\n";
    int n;
    cin >> n;
    vector<lines> linesVector;
    cout << "Enter x1, y1, x2, y2 " << n << " times, each pair of points in different lines\n";
    for (int i = 0; i < n; i++)
    {
        lines tempLine;

        cin >> tempLine.x1 >> tempLine.y1 >> tempLine.x2 >> tempLine.y2;
        linesVector.push_back(tempLine);
    }
    // Drwaing clipped Line
    cout << "Intersection points shown for any line considers intersection with both actual and extended boundary\n\n";
    for (int i = 0; i < n; i++)
    {
        // Calling clip() which in term clip the line as per window and draw it
        cout << "For " << (i + 1) << " th line\n";
        clip(linesVector[i]);
        cout << "\n--------------------------------------------------\n";
    }
    getch();
    // For Closing the graph.
    closegraph();
    return 0;
}

/*
Sample Input
Enter xmin, xmax, ymin, ymax
-3 2 1 6

How many lines?
5

Enter x1, y1, x2, y2
-4 2 -1 7
-1 5 3 8
-2 3 1 2
1 -2 3 3
-4 7 -2 10
*/
