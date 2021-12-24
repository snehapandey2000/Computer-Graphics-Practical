#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;

#define PI 3.141592653589793238
vector<pair<double, double>> coordinates;
int n; //no.of coordinates to plot
double res[][1] = {{0}, {0}, {0}};
int MAXX = 500, MAXY = 500;

//mat 2 has the coordinates and mat1 is the transformation matrix
void matrixMultiply(int r1, int c1, double mat1[][3], int r2, int c2, double mat2[][1], int res_r, int res_c, double res[][1])
{

    int x, i, j;
    for (i = 0; i < r1; i++)
    {
        for (j = 0; j < c2; j++)
        {
            res[i][j] = 0;
            for (x = 0; x < c1; x++)
            {
                res[i][j] += mat1[i][x] * mat2[x][j];
            }
        }
    }
}

void translate(double tx, double ty)
{
    double T[][3] = {{1, 0, tx}, {0, 1, ty}, {0, 0, 1}};
    for (int i = 0; i < n; i++)
    {
        double P[3][1] = {{coordinates[i].first}, {coordinates[i].second}, {1}};
        matrixMultiply(3, 3, T, 3, 1, P, 3, 1, res);
        coordinates[i].first = res[0][0];
        coordinates[i].second = res[1][0];
    }
}

void rotateAboutOrigin(double theta)
{
    double R[][3] = {{cos(theta), -1 * sin(theta), 0}, {sin(theta), cos(theta), 0}, {0, 0, 1}};
    for (int i = 0; i < n; i++)
    {
        double P[3][1] = {{coordinates[i].first}, {coordinates[i].second}, {1}};
        matrixMultiply(3, 3, R, 3, 1, P, 3, 1, res);
        coordinates[i].first = res[0][0];
        coordinates[i].second = res[1][0];
    }
}

void freeScaling(double Sx, double Sy)
{
    double S[][3] = {{Sx, 0, 0}, {0, Sy, 0}, {0, 0, 1}};
    for (int i = 0; i < n; i++)
    {
        int x = coordinates[i].first;
        int y = coordinates[i].second;
        double P[3][1] = {{x}, {y}, {1}};
        matrixMultiply(3, 3, S, 3, 1, P, 3, 1, res);
        coordinates[i].first = res[0][0];
        coordinates[i].second = res[1][0];
    }
}

void reflectAboutOrigin()
{
    double R_ORIGIN[][3] = {{-1, 0, 0}, {0, -1, 0}, {0, 0, 1}};
    for (int i = 0; i < n; i++)
    {
        int x = coordinates[i].first;
        int y = coordinates[i].second;
        double P[3][1] = {{x}, {y}, {1}};
        matrixMultiply(3, 3, R_ORIGIN, 3, 1, P, 3, 1, res);
        coordinates[i].first = res[0][0];
        coordinates[i].second = res[1][0];
    }
}

void reflectAbout_X_Axis()
{
    double REF_X_AXIS[][3] = {{1, 0, 0}, {0, -1, 0}, {0, 0, 1}};
    for (int i = 0; i < n; i++)
    {
        int x = coordinates[i].first;
        int y = coordinates[i].second;
        double P[3][1] = {{x}, {y}, {1}};
        matrixMultiply(3, 3, REF_X_AXIS, 3, 1, P, 3, 1, res);
        coordinates[i].first = res[0][0];
        coordinates[i].second = res[1][0];
    }
}

void reflectAbout_Y_Axis()
{
    double REF_Y_AXIS[][3] = {{-1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    for (int i = 0; i < n; i++)
    {
        int x = coordinates[i].first;
        int y = coordinates[i].second;
        double P[3][1] = {{x}, {y}, {1}};
        matrixMultiply(3, 3, REF_Y_AXIS, 3, 1, P, 3, 1, res);
        coordinates[i].first = res[0][0];
        coordinates[i].second = res[1][0];
    }
}

void shear_X_DirectionOrigin(double Shx)
{
    double SHR_X[][3] = {{1, Shx, 0}, {0, 1, 0}, {0, 0, 1}};
    for (int i = 0; i < n; i++)
    {
        int x = coordinates[i].first;
        int y = coordinates[i].second;
        double P[3][1] = {{x}, {y}, {1}};
        matrixMultiply(3, 3, SHR_X, 3, 1, P, 3, 1, res);
        coordinates[i].first = res[0][0];
        coordinates[i].second = res[1][0];
    }
}

void shear_Y_DirectionOrigin(double Shy)
{
    double SHR_Y[][3] = {{1, 0, 0}, {Shy, 1, 0}, {0, 0, 1}};
    for (int i = 0; i < n; i++)
    {
        int x = coordinates[i].first;
        int y = coordinates[i].second;
        double P[3][1] = {{x}, {y}, {1}};
        matrixMultiply(3, 3, SHR_Y, 3, 1, P, 3, 1, res);
        coordinates[i].first = res[0][0];
        coordinates[i].second = res[1][0];
    }
}

void shear_X_and_Y_DirectionSimultaneousOrigin(double Shx, double Shy)
{
    double SHR_X_AND_Y[][3] = {{1, Shx, 0}, {Shy, 1, 0}, {0, 0, 1}};
    for (int i = 0; i < n; i++)
    {
        int x = coordinates[i].first;
        int y = coordinates[i].second;
        double P[3][1] = {{x}, {y}, {1}};
        matrixMultiply(3, 3, SHR_X_AND_Y, 3, 1, P, 3, 1, res);
        coordinates[i].first = res[0][0];
        coordinates[i].second = res[1][0];
    }
}

int main()
{
    initwindow(2000, 1000);
    line(MAXX, 0, MAXX, 2000);
    line(0, MAXY, 2000, MAXY);
    cout << "ENTER THE NUMBER OF COORDINATES OF YOUR FIGURE\n";
    cin >> n;
    cout << "ENTER THE COORDINATES LIKE X Y ONE BY ONE\n";
    double prevX, prevY;
    for (int i = 1; i <= n; i++)
    {
        double X, Y;
        cin >> X >> Y;
        pair<double, double> P(X, Y);
        coordinates.push_back(P);
        if (i > 1)
        {
            line(prevX + MAXX, prevY + MAXY, X + MAXX, Y + MAXY);
        }
        prevX = X;
        prevY = Y;
    }
    if (n > 2)
    {
        line(prevX + MAXX, prevY + MAXY, coordinates[0].first + MAXX, coordinates[0].second + MAXY); //for joining last vertex to first vertex in case of polygon
    }

    char c = 'y';
    while (c == 'y')
    {
        cout << "CHOOSE YOUR OPERATION\n";
        int choice;
        cout << "1 Translation\n";
        cout << "2 Rotation about origin\n";
        cout << "3 Rotation about any point\n";
        cout << "4 Free scaling\n";
        cout << "5 Fixed scaling\n";
        cout << "6 Reflection about any point\n";
        cout << "7 Reflection about any line\n";
        cout << "8 Shearing in X direction\n";
        cout << "9 Shearing in Y direction\n";
        cout << "10 Shearing in X and Y direction simultaneously\n";

        cin >> choice;
        if (choice == 1)
        {
            double tx, ty;
            cout << "enter tx, ty\n";
            cin >> tx >> ty;
            translate(tx, ty);
        }

        else if (choice == 2)
        {
            cout << "enter theta in degrees\n";
            double theta; //in radians
            cin >> theta;
            theta = theta * (PI / 180);
            rotateAboutOrigin(theta);
        }

        else if (choice == 3)
        {
            double xr, yr;
            double theta; //in radians
            cout << "enter theta in degrees, pivot point\n";
            cin >> theta >> xr >> yr;
            theta = theta * (PI / 180);
            translate(-xr, -yr);
            rotateAboutOrigin(theta);
            translate(xr, yr);
        }

        else if (choice == 4)
        {
            cout << "enter Sx, Sy\n";
            double Sx, Sy;
            cin >> Sx >> Sy;
            freeScaling(Sx, Sy);
        }

        else if (choice == 5)
        {
            //fixed scaling
            double Sx, Sy, xf, yf;
            cout << "enter Sx, Sy, xf, yf\n";
            cin >> Sx >> Sy >> xf >> yf;

            translate(-xf, -yf);
            freeScaling(Sx, Sy);
            translate(xf, yf);
        }

        else if (choice == 6)
        {
            //reflect about any point
            double xRef, yRef;
            cout << "enter x, y to reflect about it\n";
            cin >> xRef >> yRef;

            translate(-xRef, -yRef);
            reflectAboutOrigin();
            translate(xRef, yRef);
        }

        else if (choice == 7)
        {
            //reflect about any LINE
            double xRef, yRef;
            cout << "Is slope of line INFINITY, i.e. of x=constant form \n";
            cout << "Enter y(yes) or n(no)\n";
            char answer;
            cin >> answer;
            if (answer == 'y')
            {
                //slope of line INFINITY
                cout << "Line in x=constant form, Enter the constant\n";
                double constant;
                cin >> constant;

                translate(-constant, 0);
                reflectAbout_Y_Axis();
                translate(constant, 0);
            }
            else
            {
                cout << "Line in y = mx + c form, Enter the m and c\n";
                double m, c;
                double thetaOfLine;
                cin >> m >> c;

                thetaOfLine = atan(m);
                translate(0, -c);
                rotateAboutOrigin(-1 * thetaOfLine);
                reflectAbout_X_Axis();
                rotateAboutOrigin(thetaOfLine);
                translate(0, c);
            }
        }

        else if (choice == 8)
        {
            //x direction shear
            double Shx;
            cout << "enter Shx\n";
            cin >> Shx;

            shear_X_DirectionOrigin(Shx);
        }

        else if (choice == 9)
        {
            //y direction shear
            double Shy;
            cout << "enter Shy\n";
            cin >> Shy;

            shear_Y_DirectionOrigin(Shy);
        }

        else if (choice == 10)
        {
            //x direction shear
            double Shx, Shy;
            cout << "enter Shx, Shy\n";
            cin >> Shx >> Shy;

            shear_X_and_Y_DirectionSimultaneousOrigin(Shx, Shy);
        }

        //printing points
        cout << "THE COORDINATES AFTER TRANSFORMATION ARE\n";
        for (int i = 0; i < n; i++)
        {
            cout << coordinates[i].first << " , " << coordinates[i].second << "\n";

            if (i > 0)
            {
                line(coordinates[i - 1].first + MAXX, coordinates[i - 1].second + MAXY, coordinates[i].first + MAXX, coordinates[i].second + MAXY);
            }
        }
        if (n > 2)
        {
            line(coordinates[n - 1].first + MAXX, coordinates[n - 1].second + MAXY, coordinates[0].first + MAXX, coordinates[0].second + MAXY);
        }
        cout << "\nApply again some transformation on the latest result, y(yes) or n(no)\n";
        cin >> c;
        if (c != 'y')
        {
            break;
        }
    }

    //graphics window waits
    getch();
    closegraph();
    return 0;
}
