#include "Vec2.h"

bool Vec2::operator == (Vec2& other) {
	return this->x == other.x && this->y == other.y;
}

bool Vec2::operator != (Vec2& other) {
	return this->x != other.x && this->y != other.y;
}

Vec2& Vec2::operator + (Vec2& other) {
	Vec2 result;
	result.x = this->x + other.x;
	result.y = this->y + other.y;
	return result;
}

Vec2& Vec2::operator - (Vec2& other) {
	Vec2 result;
	result.x = this->x - other.x;
	result.y = this->y - other.y;
	return result;
}

Vec2& Vec2::operator * (Vec2& other) {
	Vec2 result;
	result.x = this->x * other.x;
	result.y = this->y * other.y;
	return result;
}

Vec2& Vec2::operator+=(Vec2& other)
{
	Vec2 result;
	result.x = this->x + other.x;
	result.y = this->y + other.y;

	return result;
}

float Vec2::dotproduct(const Vec2& v1, const Vec2& v2) {
	float result = 0;
	result = (v1.x * v2.x) + (v1.y * v2.y);
	return result;
}

float Vec2::crossproduct(const Vec2& v1, const Vec2& v2) {
	float result;
	result = v1.x * v2.y - v1.y * v2.x;
	return result;
}

float Vec2::Length() {// AKA magnitude
	float result;
	result = (this->x * this->x) + (this->y * this->y);
	return sqrtf(result);
}

Vec2& Vec2::normalize() {
	float length = this->Length();
	this->x = this->x / length;
	this->y = this->y / length;

	return *this;
}


// -------------- SCALAR VERSIONS --------------
Vec2& Vec2::operator + (float scalar) {
	Vec2 result;
	result.x = this->x + scalar;
	result.y = this->y + scalar;
	return result;
}

Vec2& Vec2::operator - (float scalar) {
	Vec2 result;
	result.x = this->x - scalar;
	result.y = this->y - scalar;
	return result;
}

Vec2& Vec2::operator * (float scalar) {
	Vec2 result;
	result.x = this->x * scalar;
	result.y = this->y * scalar;
	return result;
}

Vec2& Vec2::operator / (float scalar) {
	Vec2 result;
	result.x = this->x / scalar;
	result.y = this->y / scalar;
	return result;
}