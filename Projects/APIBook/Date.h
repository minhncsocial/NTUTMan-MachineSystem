#ifndef BIRTHDAY_H
#define BIRTHDAY_H

#pragma once
class Date
{
public:
	Date(int year, int month, int day);
	~Date(void);
};

class Year
{
public:
	explicit Year(int yyyy) : mYear(yyyy){}
	int GetYear() const { return mYear;}
private:
	int mYear;
};

class Month
{
public:
	explicit Month(int mm) : mMonth(mm){}
	int GetMonth() const { return mMonth;}
	static Month Jan() { return Month(1);}
	static Month Feb() { return Month(2);}
	static Month Mar() { return Month(3);}
	static Month Apr() { return Month(4);}
	static Month May() { return Month(5);}
	static Month Jun() { return Month(6);}
	static Month Jul() { return Month(7);}
	static Month Aug() { return Month(8);}
	static Month Sep() { return Month(9);}
	static Month Oct() { return Month(10);}
	static Month Nov() { return Month(11);}
	static Month Dec() { return Month(12);}
private:
	int mMonth;
};

class Day
{
public:
	explicit Day(int dd) : mDay(dd){}
	int GetDay() const { return mDay;}
private:
	int mDay;
};

#endif
