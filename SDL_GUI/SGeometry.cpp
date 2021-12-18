#include "SGeometry.h"
#include<cmath>
SPoint::SPoint()
	:_x(0), _y(0)
{
}

SPoint::SPoint(int x, int y)
	: _x(x), _y(y)
{
}

SPoint SPoint::operator+(const SPoint& point) const
{
	return SPoint(this->_x + point._x, this->_y + point._y);
}

SPoint SPoint::operator-(const SPoint& point) const
{
	return SPoint(this->_x - point._x, this->_y - point._y);;
}

bool SPoint::operator!=(const SPoint& point) const
{
	return (this->x() != point.x() || this->y() != point.y());
}

bool SPoint::operator==(const SPoint& point) const
{
	return (this->x() == point.x() && this->y() == point.y());
}

int SPoint::x()const
{
	return _x;
}

int SPoint::y()const
{
	return _y;
}

std::ostream& operator<<(std::ostream& out, const SPoint& point)
{
	out << "SPoint("<<point.x()<<","<<point.y()<<") ";
	return out;
}

/*@ SSize*/
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
	: SRect(topLeft.x(), topLeft.y(), size.w, size.h)
{
}

SRect::SRect(const SPoint& topLeft, const SPoint& bottomRight)
	: _x1(topLeft.x()), _y1(topLeft.y()), _x2(bottomRight.x()), _y2(bottomRight.y())
{
}

bool SRect::contains(const SRect& rect, bool proper) const
{
	if (proper && this->contains(rect._x1, rect._y1) && this->contains(rect._x2, rect._y2))	//完全包含
	{
		return true;
	}
	else if(!proper && this->contains(rect._x1, rect._y1) || this->contains(rect._x2, rect._y2))
	{
		return true;
	}
	return false;
}

bool SRect::contains(const SPoint& point) const
{
	return contains(point.x(), point.y());
}

bool SRect::contains(int x, int y) const
{
	if (x >= _x1 && x <= _x2 && y >= _y1 && y <= _y2)
		return true;
	return false;
}

SPoint SRect::leftTop() const
{
	return SPoint(_x1,_y1);
}

SPoint SRect::leftBottom() const
{
	return SPoint(_x1,_y2);
}

SPoint SRect::rightTop() const
{
	return SPoint(_x2,_y1);
}

SPoint SRect::rightBottom() const
{
	return SPoint(_x2,_y2);
}


SRect SRect::intersected(const SRect& rect) const
{
	//一个矩形的左上角x大于另一个矩形的右下角x，不相交 （左右判断）
	if (_x1 > rect._x2 || _x2 < rect._x1)
	{
		return SRect();
	}

	//一个矩形的左上角y大于另一个矩形的右下角y，不相交 （上下判断）
	if (_y1 > rect._y2 || _y2 < rect._y1)
	{
		return SRect();
	}

	//否则相交
	SRect tmp;
	tmp._x1 = std::max(_x1,rect._x1);
	tmp._x2 = std::min(_x2,rect._x2);
	tmp._y1 = std::max(_y1,rect._y1);
	tmp._y2 = std::min(_y2,rect._y2);
	return tmp;
}

SSize SRect::size() const
{
	return SSize(width(),height());
}

void SRect::setSize(int width, int height)
{
	_x2 = _x1 + width;
	_y2 = _y1 + height;
}

int SRect::width() const
{
	return _x2-_x1;
}

int SRect::height() const
{
	return _y2 - _y1;
}

void SRect::moveLeft(Sint32 pos) noexcept
{
	_x2 += (pos - _x1);	//把右边的x也移动pos大小，不过要注意方向
	_x1 = pos;
}

void SRect::moveTop(Sint32 pos) noexcept
{
	_y2 += (pos - _y1);
	_y1 = pos;
}

void SRect::moveRight(Sint32 pos) noexcept
{
	_x1 += (pos - _x2);
	_x2 = pos;
}

void SRect::moveBottom(Sint32 pos) noexcept
{
	_y1 += (pos - _y2);
	_y2 = pos;
}

void SRect::moveLeftTop(const SPoint& pos)
{
	moveLeft(pos.x());
	moveTop(pos.y());
}

void SRect::moveLeftBottom(const SPoint& pos)
{
	moveLeft(pos.x());
	moveBottom(pos.y());
}

void SRect::moveRightTop(const SPoint& pos)
{
	moveRight(pos.x());
	moveTop(pos.y());
}

void SRect::moveRightBottom(const SPoint& pos)
{
	moveRight(pos.x());
	moveBottom(pos.y());
}




std::ostream& operator<<(std::ostream& out, const SRect& rect)
{
	out << "SRect(" << rect._x1 << "," << rect._y1 << "," << rect._x2- rect._x1 << "," << rect._y2-rect._y1<<") ";
	return out;
}
