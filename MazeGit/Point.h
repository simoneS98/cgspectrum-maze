#pragma once
#include <ostream>
class Point
{
public:
	int x;
	int y;

	Point(int x, int y);

	Point operator+(Point p2);

	Point* operator+=(Point p2);

	friend std::ostream& operator<<(std::ostream& os, const Point& dt);

	bool operator!=(Point p2);

};

