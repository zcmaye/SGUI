#include "SGeometry.h"

SPoint::SPoint()
	:x(0), y(0)
{
}

SPoint::SPoint(int x, int y)
	: x(x), y(y)
{
}

SPoint SPoint::operator+(const SPoint& point) const
{
	return SPoint(this->x + point.x, this->y + point.y);
}

SSize::SSize()
	: w(0), h(0)
{
}

SSize::SSize(int w, int h)
	: w(w), h(h)
{
}

/*@ SRect*/
SRect::SRect()
	: _x1(0), _y1(0), _x2(0), _y2(0)
{
}

SRect::SRect(int x, int y, int width, int height)
	: _x1(x), _y1(y), _x2(x + width), _y2(y + height)
{

}

SRect::SRect(const SPoint& topLeft, const SSize& size)
	: SRect(topLeft.x, topLeft.y, size.w, size.h)
{
}

SRect::SRect(const SPoint& topLeft, const SPoint& bottomRight)
	: _x1(topLeft.x), _y1(topLeft.y), _x2(bottomRight.x), _y2(bottomRight.y)
{
}

bool SRect::contains(const SRect& rect, bool proper) const
{
	if (proper && this->contains(rect._x1, rect._y1) && this->contains(rect._x2, rect._y2))	//完全包含
	{
		return true;
	}
	else if(this->contains(rect._x1, rect._y1) || this->contains(rect._x2, rect._y2))
	{
		return true;
	}
	return false;
}

bool SRect::contains(const SPoint& point) const
{
	return contains(point.x,point.y);
}

bool SRect::contains(int x, int y) const
{
	if (x >= _x1 && x <= _x2 && y >= _y1 && y <= _y2)
		return true;
	return false;
}


std::ostream& operator<<(std::ostream& out, const SRect& rect)
{
	out << "SRect(" << rect._x1 << "," << rect._y1 << "," << rect._x2 << "," << rect._y2;
	return out;
}
