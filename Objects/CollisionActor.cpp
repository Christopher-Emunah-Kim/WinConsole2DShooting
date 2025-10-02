#include "pch.h"
#include "CollisionActor.h"
#include <cmath>
#include "Position.h"


bool CollisionActor::CheckCircleToCircleCollision(const CollisionActor* from, const CollisionActor* to)
{
	if(!from || !to)
		return false;

	const Position& pos1 = from->GetPosition();
	const Position& pos2 = to->GetPosition();

	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	float distanceSquared = dx * dx + dy * dy;

	float radiusSum = from->m_collisionRadius + to->m_collisionRadius;

	return distanceSquared <= radiusSum * radiusSum;
}

bool CollisionActor::CheckRectToRectCollision(const CollisionActor* from, const CollisionActor* to)
{
	if (!from || !to)
		return false;

	const Position& pos1 = from->GetPosition();
	const Position& pos2 = to->GetPosition();

	float fromLeft = pos1.x - from->m_width * 0.5f;
	float fromRight = pos1.x + from->m_width * 0.5f;
	float fromTop = pos1.y - from->m_height * 0.5f;
	float fromBottom = pos1.y + from->m_height * 0.5f;

	float toLeft = pos2.x - to->m_width * 0.5f;
	float toRight = pos2.x + to->m_width * 0.5f;
	float toTop = pos2.y - to->m_height * 0.5f;
	float toBottom = pos2.y + to->m_height * 0.5f;

	return !(fromLeft > toRight || fromRight < toLeft || fromTop > toBottom || fromBottom < toTop);
}

bool CollisionActor::CheckRectToCircleCollision(const CollisionActor* fromRect, const CollisionActor* toCircle)
{
	if (!fromRect || !toCircle)
		return false;

	const Position& rectPos = fromRect->GetPosition();
	const Position& circlePos = toCircle->GetPosition();

	float rectLeft = rectPos.x - fromRect->m_width * 0.5f;
	float rectRight = rectPos.x + fromRect->m_width * 0.5f;
	float rectTop = rectPos.y - fromRect->m_height * 0.5f;
	float rectBottom = rectPos.y + fromRect->m_height * 0.5f;

	float closestX = circlePos.x;
	float closestY = circlePos.y;

	if(closestX < rectLeft)
		closestX = rectLeft;
	else if(closestX > rectRight)
		closestX = rectRight;

	if (closestY < rectTop)
		closestY = rectTop;
	else if (closestY > rectBottom)
		closestY = rectBottom;

	float dx = circlePos.x - closestX;
	float dy = circlePos.y - closestY;
	float distanceSquared = dx * dx + dy * dy;
	
	return distanceSquared <= (toCircle->m_collisionRadius * toCircle->m_collisionRadius);
}

void CollisionActor::PrintCollisionResult(const CollisionActor* target)
{
	if (CheckCircleToCircleCollision(this, target))
	{
		OutputDebugStringA("Circle to Circle Collision Detected!\n");
	}
	else
	{
		OutputDebugStringA("No Circle to Circle Collision.\n");
	}

	if (CheckRectToRectCollision(this, target))
	{
		OutputDebugStringA("Rect to Rect Collision Detected!\n");
	}
	else
	{
		OutputDebugStringA("No Rect to Rect Collision.\n");
	}

	if (CheckRectToCircleCollision(this, target))
	{
		OutputDebugStringA("Circle to Rect Collision Detected!\n");
	}
	else
	{
		OutputDebugStringA("No Circle to Rect Collision.\n");
	}
}
