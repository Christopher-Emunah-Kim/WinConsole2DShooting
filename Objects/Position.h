#pragma once

struct Position
{
	Position() : x(0), y(0) {}
	Position(float x, float y) : x(x), y(y) {}

	float x;
	float y;
};