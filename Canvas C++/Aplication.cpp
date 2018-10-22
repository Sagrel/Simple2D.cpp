#include <vector>

#include "Simple2D\Simple2D.h"

using namespace std;



struct Point
{
	Point(int x, int y) : x(x), y(y) {}


	int x, y;
};

struct Color
{
	int r, g, b;
};

struct Line
{
	Line(int x1, int y1, int x2, int y2)
	{
		length = round(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));

		x = (x2 + x1) / 2;
		y = (y2 + y1) / 2;

		angle = atan2(y2 - y1, x2 - x1);
	}

	Line(const Line& l)	:	x(l.x), y(l.y), length(l.length), angle(l.angle)	{}

	void Draw()
	{
		DrawLine(x, y, length, angle, 5);
	}


	int x, y;
	int length;
	float angle;
};


vector<Line> createLines(const vector<Point>& p)
{
	vector<Line> l;
	l.reserve(p.size());
	for (int j = 0; j < p.size() - 1; j++)
	{
		for (int i = j + 1; i < p.size(); i++)
		{
			Line t(p[j].x, p[j].y, p[i].x, p[i].y);

			if (t.length < 5) continue;
			l.emplace_back(t);
			j = i - 1;
			break;
		}	
	}
	l.shrink_to_fit();
	
	return l;
}

struct Trace
{
	Trace(vector<Line> l, Color c) : l(l), c(c) {};

	vector<Line> l;
	Color c;
};

vector<Trace> trazos;



vector<Point> points;

Color col = { 0,0,255 };



void Setup()
{

}

void Loop()
{
	Clear();	

	SetColor(255, 0, 0);
	if (Buttom(-Width() / 2 + 20, -Height() / 2 + 20, 20))
	{
		col = { 255, 0, 0 };
	}
	SetColor(0, 255, 0);
	if (Buttom(-Width() / 2 + 40, -Height() / 2 + 20, 20))
	{
		col = { 0, 255, 0 };
	}
	SetColor(0, 0, 255);
	if (Buttom(-Width() / 2 + 20, -Height() / 2 + 40, 20))
	{
		col = { 0, 0, 255 };
	}

	if (MouseButtonDown(0) || MouseButton(0))
	{
		points.emplace_back(Point( MouseX(), MouseY() ));
	}
	else if (MouseButtonDown(2))
	{
		if (trazos.size() != 0)
		{
			trazos.pop_back();
		}
	}
	if (MouseButtonUp(0))
	{
		trazos.emplace_back(Trace(createLines(points), col));
		points.clear();
	}
	   

	for (auto& t : trazos)
	{
		SetColor(t.c.r, t.c.g, t.c.b);
		for (auto& i : t.l)
		{
			i.Draw();
		}
	}

	SetColor(col.r, col.g, col.b);
	for (int j = 1; j < points.size(); j++)
	{
		DrawLine(points[j - 1].x, points[j - 1].y, points[j].x, points[j].y, 5);
	}
}


