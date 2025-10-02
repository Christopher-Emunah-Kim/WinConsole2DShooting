#include "pch.h"
#include "PhysicsComponent.h"
#include "../Objects/K_Actor.h"

PhysicsComponent::PhysicsComponent(Actor* owenr, ECollisionType colType, EPhysicsLayer physicsType)
	: Component(owenr), m_collisionType(colType), m_physicsLayer(physicsType), m_data1(0.0f), m_data2(0.0f)
{
}


bool PhysicsComponent::OnCollision(PhysicsComponent* other) const
{
	bool result = false;

	if (!other || other == this) 
	{
		return false;
	}

	if(this->GetPhysicsLayer() == EPhysicsLayer::None || other->GetPhysicsLayer() == EPhysicsLayer::None)
	{
		return false;
	}

	if (m_collisionType == other->GetCollisionType())
	{
		switch (m_collisionType)
		{
			case ECollisionType::Circle:
				result = CheckCircleToCircleOverlap(this, other);
				break;
			case ECollisionType::Rect:
				result = CheckRectToRectOverlap(this, other);
				break;
		}
	}
	else
	{
		result = CheckRectToCircleOverlap(this, other);
	}


	return result;
}

bool PhysicsComponent::CheckCircleToCircleOverlap(const PhysicsComponent* from, const PhysicsComponent* to) const
{
	if (!from || !to)
		return false;

	const Position& pos1 = from->GetOwner()->GetPosition();
	const Position& pos2 = to->GetOwner()->GetPosition();

	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	float distanceSquared = dx * dx + dy * dy;

	float radiusSum = from->GetRadius() + to->GetRadius();

	return distanceSquared <= radiusSum * radiusSum;
}

bool PhysicsComponent::CheckRectToRectOverlap(const PhysicsComponent* from, const PhysicsComponent* to) const
{
	if (!from || !to)
		return false;

	const Position& pos1 = from->GetOwner()->GetPosition();
	const Position& pos2 = to->GetOwner()->GetPosition();

	float fromLeft = pos1.x - from->GetWidth() * 0.5f;
	float fromRight = pos1.x + from->GetWidth() * 0.5f;
	float fromTop = pos1.y - from->GetHeight() * 0.5f;
	float fromBottom = pos1.y + from->GetHeight() * 0.5f;

	float toLeft = pos2.x - to->GetWidth() * 0.5f;
	float toRight = pos2.x + to->GetWidth() * 0.5f;
	float toTop = pos2.y - to->GetHeight() * 0.5f;
	float toBottom = pos2.y + to->GetHeight() * 0.5f;

	return !(fromLeft > toRight || fromRight < toLeft || fromTop > toBottom || fromBottom < toTop);
}

bool PhysicsComponent::CheckRectToCircleOverlap(const PhysicsComponent* from, const PhysicsComponent* to) const
{
	if (!from || !to)
		return false;

	const PhysicsComponent* circle;
	const PhysicsComponent* rect;

	if (from->GetCollisionType() == ECollisionType::Circle)
	{
		circle = from;
		rect = to;
	}
	else
	{
		circle = to;
		rect = from;
	}

	const Position& rectPos = rect->GetOwner()->GetPosition();
	const Position& circlePos = circle->GetOwner()->GetPosition();

	float rectLeft = rectPos.x - rect->GetWidth() * 0.5f;
	float rectRight = rectPos.x + rect->GetWidth() * 0.5f;
	float rectTop = rectPos.y - rect->GetHeight() * 0.5f;
	float rectBottom = rectPos.y + rect->GetHeight() * 0.5f;

	float closestX = circlePos.x;
	float closestY = circlePos.y;

	if (closestX < rectLeft)
		closestX = rectLeft;
	else if (closestX > rectRight)
		closestX = rectRight;

	if (closestY < rectTop)
		closestY = rectTop;
	else if (closestY > rectBottom)
		closestY = rectBottom;

	float dx = circlePos.x - closestX;
	float dy = circlePos.y - closestY;
	float distanceSquared = dx * dx + dy * dy;

	return distanceSquared <= (circle->GetRadius() * circle->GetRadius());
}
