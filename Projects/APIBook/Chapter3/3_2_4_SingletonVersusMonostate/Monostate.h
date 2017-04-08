#ifndef MONOSTATE_H
#define MONOSTATE_H

#pragma once


class Rectangle
{
public:
	int GetHeight() const { return sHeight;}
	int GetWidth() const { return sWidth;}

	void SetHeight(int height) const { sHeight = height;}
	void SetWidth(int width) const { sWidth = width;}

private:
	static int sHeight;
	static int sWidth;
};


class Temperature
{
public:
	int GetTemperature() const;
	void SetTemperature(int temperature) const;

private:
	static int sTemperature;
};




#endif