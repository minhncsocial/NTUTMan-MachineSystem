#ifndef COORD2D_H
#define COORD2D_H

#include <iostream>
template <typename T>
class Coord2D
{
public:
	Coord2D(T x, T y) : mX(x), mY(y) {};
	
	T GetX() const { return mX;}
	T GetY() const { return mY;}

	void SetX(T x) { mX x;}
	void SetY(T y) { mY y;}

	void Add(T dx, T dy) { mX + dx; mY + dy;}
	void Multiply(T dx, T dy) { mX * dx; mY * dy;}
private:
	T mX;
	T mY;
};

#endif