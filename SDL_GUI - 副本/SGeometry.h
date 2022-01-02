#pragma once
#include<SDL_rect.h>
#include<iostream>
class SPoint
{
public:
	SPoint();
	SPoint(int x, int y);
	int x()const;
	int y()const;

	SPoint operator+(const SPoint& point) const;
	SPoint operator-(const SPoint& point) const;
	bool operator!=(const SPoint& point) const;
	bool operator==(const SPoint& point) const;
	friend std::ostream& operator<<(std::ostream& out, const SPoint& point);
private:
	int _x;
	int _y;
};

struct SSize
{
	SSize();
	SSize(int w, int h);
	int w;
	int h;
};

class SRect
{
public:
	SRect();
	SRect(int x, int y, int width, int height);
	SRect(const SPoint& topLeft, const SSize& size);
	SRect(const SPoint& topLeft, const SPoint& bottomRight);

	bool contains(const SRect& rect, bool proper = false) const;
	bool contains(const SPoint& point) const;
	bool contains(int x, int y) const;

	inline int x1() { return _x1; }
	inline int y1() { return _y1; }
	inline int x2() { return _x2; }
	inline int y2() { return _y2; }

	SPoint leftTop() const;
	SPoint leftBottom() const;
	SPoint rightTop() const;
	SPoint rightBottom() const;


	 void moveLeft(Sint32 pos) noexcept;
	 void moveTop(Sint32 pos) noexcept;
	 void moveRight(Sint32 pos) noexcept;
	 void moveBottom(Sint32 pos) noexcept;
	//移动矩形，将指定位置移动到给定位置。 矩形的大小不变。  
	void moveLeftTop(const SPoint& pos);
	void moveLeftBottom(const SPoint& pos);
	void moveRightTop(const SPoint& pos);
	void moveRightBottom(const SPoint& pos);

	//两个矩形相交部分
	SRect intersected(const SRect& rectangle) const;

	SSize size() const;
	void setSize(int width,int height);
	int width()const;
	int height()const;

	inline SDL_Rect sdlRect()
	{ 
		return SDL_Rect{ _x1,_y1, _x2 - _x1,_y2 - _y1 }; 
	}
	friend std::ostream& operator<<(std::ostream& out, const SRect& rect);
	bool operator==(const SRect& rect)const;
	bool operator!=(const SRect& rect)const;
private:
	int _x1;
	int _y1;
	int _x2;
	int _y2;
};

