#pragma once
#include "common.h"

class CTransform {

public :
	Vec2 Position = { 0.0f, 0.0f };
	Vec2 Scale = { 0.0f, 0.0f };
	Vec2 Speed = { 0.0f, 0.0f };
	float Angle = 0.0f;

	CTransform() {};
	CTransform(Vec2 pos, Vec2 scale, Vec2 speed, float angle) : Position(pos), Scale(scale), Speed(speed), Angle(angle) {};
};

class CShape {
public:
	sf::CircleShape shape;


	CShape() : shape(sf::CircleShape(10.0f)) {};
	CShape(float radius, int points, float outlinethickness, sf::Color fillcolor, sf::Color outlinecolor) :shape(radius, points) {
		shape.setFillColor(fillcolor);
		shape.setOutlineThickness(outlinethickness);
		shape.setOutlineColor(outlinecolor);
		shape.setOrigin(sf::Vector2f(radius, radius));
	}
};

class CCollision {
public:
	float radius = 0;

	CCollision() {};
	CCollision(float radius) : radius(radius) {};
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

	CScore(int value): score(value) {}
};

class CLifeSpan {
	int total = 0;
	int remaining = 0;

	CLifeSpan() {};
	CLifeSpan(int total) : total(total), remaining(total){}
};



