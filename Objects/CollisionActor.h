#pragma once
#include "Objects/K_Actor.h"

class CollisionActor : public Actor
{
public:
	CollisionActor() = delete;
	explicit CollisionActor(EObjectType type)
		: Actor(type)
	{
		m_width = static_cast<int>(m_collisionRadius * 2);
		m_height = static_cast<int>(m_collisionRadius * 2);
	};

private:
	bool CheckCircleToCircleCollision(const CollisionActor* from, const CollisionActor* to);
	bool CheckRectToRectCollision(const CollisionActor* from, const CollisionActor* to);
	bool CheckRectToCircleCollision(const CollisionActor* fromRect, const CollisionActor* toCirtle);

public:
	virtual void Init() override {}
	virtual void Tick(float deltaSeconds) override {}
	virtual void Render(Gdiplus::Graphics& graphics) override { }
	virtual void Release() override {}
	virtual void OverlapWith(Actor* other) override {}


	void PrintCollisionResult(const CollisionActor* target);

private:
	float m_collisionRadius = 25.0f;
};

