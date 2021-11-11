#pragma once
/*
	BadCon.h - calls an annoyingly long print statement for its constructor. Useful for testing memory management in Vector
*/
#include <cstdio>

class BadCon
{
public:
	BadCon();
	BadCon(int);
	~BadCon();
	bool operator==(const BadCon&); // This was a waste of time
	int m_num; // and this is bad practice

private:
};

inline BadCon::BadCon()
{
	printf("This is a very long and verbose way of showing that an object of the type, BadCon, has just been initialized and has called its constructor\n");
}

inline BadCon::BadCon(int num) 
{
	m_num = num;
	printf("This is a very long and verbose way of showing that an object of the type, BadCon, has just been initialized and has called its constructor\n");
}

inline BadCon::~BadCon()
{
}

inline bool BadCon::operator==(const BadCon& old_obj)
{
	return (old_obj.m_num == m_num);
}
