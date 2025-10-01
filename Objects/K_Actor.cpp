#include "pch.h"
#include "K_Actor.h"


Actor::Actor()
	: m_posX(0.0), m_posY(0.0), m_width(0), m_height(0)
{
}

Actor::~Actor()
{
}


void Actor::SetPosition(double x, double y)
{
	m_posX = x;
	m_posY = y;
}

void Actor::SetSize(int width, int height)
{
	m_width = width;
	m_height = height;
}
