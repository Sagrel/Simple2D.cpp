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



vector<unique_ptr<pair<vector<Point>, Color>>> lines;

Color col = { 0,0,255 };

int index = 0;

bool r_b = false;

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

	if (MouseButtonDown(0))
	{
		lines.push_back(make_unique<pair<vector<Point>, Color>>());
		lines[index]->first.push_back({ MouseX(), MouseY() });
		lines[index]->second = col;
	}
	else if (MouseButton(0))
	{
		lines[index]->first.push_back({ MouseX(), MouseY() });
	}
	else if (MouseButtonDown(2))
	{
		if (lines.size() != 0)
		{
			index--;
			lines.pop_back();
		}
	}
	if (MouseButtonUp(0))
	{
		index++;
	}



	for (auto& l : lines)
	{
		SetColor(l->second.r, l->second.g, l->second.b);
		for (int j = 1; j < l->first.size(); j++)
		{
			DrawLine(l->first[j - 1].x, l->first[j - 1].y, l->first[j].x, l->first[j].y, 2);
		}
	}
}


