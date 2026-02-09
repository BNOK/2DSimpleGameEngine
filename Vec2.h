
//THIS IS A CUSTOM CLASS MADE FOR SPECIFIC NEEDS FOR THE 2D GAME 
//this class will be only used for this assignment for the moment
#pragma once
#include "common.h"

class Vec2
{
public :
	float x;
	float y;

	Vec2() : x(0), y(0) {};
	Vec2(float inx, float iny) :x(static_cast<float>(inx)), y(static_cast<float>(iny)) {};


	bool operator == (Vec2& other);
	bool operator != (Vec2& other);
	Vec2& operator + (Vec2& other);
	Vec2& operator - (Vec2& other);
	Vec2& operator * (Vec2& other);
	Vec2& operator += (Vec2& other);

	float dotproduct(const Vec2& v1, const Vec2& v2);

	float crossproduct(const Vec2& v1, const Vec2& v2);

	float Length();

	Vec2& normalize();

	// -------------- SCALAR VERSIONS --------------
	Vec2& operator + (float scalar);
	Vec2& operator - (float scalar);
	Vec2& operator * (float scalar);
	Vec2& operator / (float scalar);
};

