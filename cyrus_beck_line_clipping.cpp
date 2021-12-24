#include <bits/stdc++.h>
#include <graphics.h>

#define f first
#define s second
#define pdd pair<double, double>
#define vecpdd vector<pdd>
using namespace std;
int xNewOrg, yNewOrg;

float xNew(float x)
{
	return x + xNewOrg;
}
float yNew(float y)
{
	return -y + yNewOrg;
}

double dot_product(pdd v1, pdd v2)
{
	return v1.f * v2.f + v1.s * v2.s;
}

pdd normal_unit_vector(pdd p1, pdd p2, pdd extra)
{
	pdd ans = make_pair(p2.s - p1.s, -(p2.f - p1.f));

	//below if ensures that the normal vector is pointing towards INSIDE of the polygon
	if (dot_product({extra.f - p1.f, extra.s - p1.s}, ans) < 0)
	{
		ans.f *= -1;
		ans.s *= -1;
	}
	double magnitude = sqrt(ans.f * ans.f + ans.s * ans.s);
	ans.f /= magnitude;
	ans.s /= magnitude;
	return ans;
}

void cyrus_clipping(vecpdd vec, pdd p1, pdd p2)
{

	cout << setprecision(2) << fixed;
	double tl_max = 0, tu_min = 1, tl, tu;
	pdd D = make_pair(p2.f - p1.f, p2.s - p1.s);

	cout << "D = [" << D.f << " " << D.s << "]" << endl
		 << endl;
	cout << "Edge \t n \t\t f \t\t W \t\t D.n \t D.w \t t" << endl
		 << endl;
	int sz = vec.size();
	for (int i = 0; i < sz; ++i)
	{
		pdd n = normal_unit_vector(vec[i], vec[(i + 1) % sz], vec[(i + 2) % sz]);
		pdd w = make_pair(p1.f - vec[i].f, p1.s - vec[i].s);

		double wn = dot_product(n, w);
		double Dn = dot_product(n, D);

		//to handle the case when D.N = 0
		if (Dn == 0)
		{
			Dn = 1e-9;
		}

		double t = -(wn) / (Dn);

		if (Dn > 0)
		{
			tl_max = max(tl_max, t);
		}
		else
		{
			tu_min = min(tu_min, t);
		}

		cout << "V" << i + 1 << "V" << (i + 1) % sz + 1 << "\t";
		cout << "[" << n.f << " " << n.s << "]\t";
		cout << "[" << vec[i].f << " " << vec[i].s << "]\t";
		cout << "[" << w.f << " " << w.s << "]\t";
		cout << Dn << "\t";
		cout << wn << "\t";
		cout << t << endl;
	}

	cout << endl;

	cout << "tl_max = " << tl_max << endl;
	cout << "tu_min = " << tu_min << endl;

	if (tl_max > tu_min || tl_max > 1 || tu_min < 0)
	{
		cout << "Line is completely outside" << endl;
	}
	else
	{
		pdd finalP1 = make_pair(p1.f + D.f * tl_max, p1.s + D.s * tl_max);
		pdd finalP2 = make_pair(p1.f + D.f * tu_min, p1.s + D.s * tu_min);

		cout << "Final P1: " << finalP1.f << ", " << finalP1.s << endl;
		cout << "Final P2: " << finalP2.f << ", " << finalP2.s << endl;

		setcolor(YELLOW);
		line(xNew(finalP1.f), yNew(finalP1.s), xNew(finalP2.f), yNew(finalP2.s));
	}
}

int main()
{
	int w, h;
	w = 1500, h = 900;
	initwindow(w, h);
	line(w / 2, 0, w / 2, h);
	line(0, h / 2, w, h / 2);
	xNewOrg = w / 2;
	yNewOrg = h / 2;

	vecpdd vec;
	pdd p1, p2;
	int n;
	cout << "Enter the number of vertices for your convex polygon window :): ";
	cin >> n;
	vec.resize(n);
	cout << "Enter points in clockwise or anticlockwise order: " << endl;
	for (int i = 0; i < n; ++i)
	{
		cout << "V" << i + 1 << ": ";
		cin >> vec[i].f >> vec[i].s;
		if (i > 0)
		{
			line(xNew(vec[i - 1].f), yNew(vec[i - 1].s), xNew(vec[i].f), yNew(vec[i].s));
		}
	}
	line(xNew(vec[0].f), yNew(vec[0].s), xNew(vec[n - 1].f), yNew(vec[n - 1].s));
	cout << endl
		 << "Enter number of lines to clip: ";
	cin >> n;
	cout << endl
		 << "Enter end point coordinates of each line one by one: " << endl;
	while (n--)
	{
		cout << "P1: ";
		cin >> p1.f >> p1.s;
		cout << "P2: ";
		cin >> p2.f >> p2.s;
		setcolor(WHITE);
		line(xNew(p1.f), yNew(p1.s), xNew(p2.f), yNew(p2.s));
		cyrus_clipping(vec, p1, p2);
	}
	getch();
	closegraph();
	return 0;
}

/*
Enter no of points of polygon(window): 8
Enter points in clockwise or anticlockwise order:
V1: 200 300
V2: 400 100
V3: 400 -100
V4: 200 -200
V5: -200 -200
V6: -400 -100
V7: -400 100
V8: -200 300

Enter no of lines: 2

Enter coordinates of line:
P1: -500 100
P2: 500 250
P1: -300 100
P2: 350 100
*/
