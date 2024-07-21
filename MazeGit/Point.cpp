#include "Point.h"

Point::Point(int x, int y)
	: x(x)
	, y(y)
{
}

Point Point::operator+(Point p2)
{
	this->x += p2.x;
	this->y += p2.y;

	return Point(this->x, this->y);
	//return this;	
}

Point* Point::operator+=(Point p2)
{
	this->x += p2.x;
	this->y += p2.y;

	return this;
}

bool Point::operator!=(Point p2)
{
	return this->x != p2.x && this->y != p2.y;
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
	os << "(" << p.x << "," << p.y << ")";
	return os;
}
