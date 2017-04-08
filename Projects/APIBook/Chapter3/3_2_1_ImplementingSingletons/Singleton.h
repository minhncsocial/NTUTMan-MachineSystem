#pragma once
class Singleton
{
public:
	static Singleton &GetInstance();
	int GetState();

private:
	Singleton(void);
	~Singleton(void);
	Singleton(const Singleton&);
	const Singleton &operator = (const Singleton &);
};

