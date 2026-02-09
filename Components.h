#pragma once
#include "common.h"

class CTransform {

public :
Vec2	Position;
Vec2	Scale;
Vec2	Speed;
float	Angle;

	CTransform()
	{
		Position = {0.0f, 0.0f};
		Scale = {10.0f,10.0f};
		Speed = {1.0f, 1.0f};
		Angle = 0.0f;
	};
	CTransform(Vec2 pos , Vec2 scale , Vec2 speed , float angle) : Position(pos), Scale(scale), Speed(speed), Angle(angle)
	{};
	CTransform(Vec2 pos) : Position(pos), Scale({10.0f, 10.0f}), Speed({10.0f, 10.0f}), Angle(0.0f)
	{};
	
};

class CShape {
public:
	sf::CircleShape shape;


	CShape() : shape(sf::CircleShape(10.0f)) {};
	CShape(float radius, int points, float outlinethickness, sf::Color fillcolor, sf::Color outlinecolor) 
		:shape(radius, points) {
		//shape = sf::CircleShape(radius, points);
		shape.setFillColor(fillcolor);
		shape.setOutlineThickness(outlinethickness);
		shape.setOutlineColor(outlinecolor);
		shape.setOrigin(sf::Vector2f(radius, radius));
	}
};

class CCollision {
public:
	float radius = 0;

	CCollision() : radius(10.0f)
	{};
	CCollision(float radius = 10.0f) : radius(radius) {};
};

class CInput {
public :
	bool right = 0;
	bool left = 0;
	bool up = 0;
	bool down = 0;

	CInput() {};
};

class CScore {
public:
	int score = 0;

	CScore() {};
	CScore(int value = 0): score(value) {}
};

class CLifeSpan {
	int total		= 0;
	
	CLifeSpan() {};
	CLifeSpan(int total = 0) : total(total){}
};



