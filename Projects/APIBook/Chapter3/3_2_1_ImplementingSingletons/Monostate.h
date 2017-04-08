#pragma once
class Monostate
{
public:
	int GetTheAnswer() const { return sAnswer;}
private:
	static int sAnswer;
	/*Monostate(void);
	~Monostate(void);*/
};

