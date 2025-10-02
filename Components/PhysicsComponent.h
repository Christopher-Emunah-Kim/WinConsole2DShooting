#pragma once
#include "Component.h"	

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(Actor* owenr, ECollisionType colType = ECollisionType::None, EPhysicsLayer physicsType = EPhysicsLayer::None);

	~PhysicsComponent() override = default;

private:
	bool CheckCircleToCircleOverlap(const PhysicsComponent* from, const PhysicsComponent* to) const;
	bool CheckRectToRectOverlap(const PhysicsComponent* from, const PhysicsComponent* to) const;
	bool CheckRectToCircleOverlap(const PhysicsComponent* fromRect, const PhysicsComponent* toCircle) const;

public:
	virtual void Init() override {}
	virtual void Tick(float deltaSeconds) override {}
	virtual void Release() override {}

	bool OnCollision(PhysicsComponent* other) const;

	inline float GetRadius() const { return m_data1; } //원형 충돌 반지름 반환
	inline float GetWidth() const { return m_data1; }  //사각형 충돌 너비 반환
	inline float GetHeight() const { return m_data2; } //사각형 충돌 높이 반환

	inline ECollisionType GetCollisionType() const { return m_collisionType; }
	inline EPhysicsLayer GetPhysicsLayer() const { return m_physicsLayer; }

	inline void SetRadius(float radius) { m_data1 = radius; } 
	inline void SetWidth(float width) { m_data1 = width; }
	inline void SetHeight(float height) { m_data2 = height; }

private:
	ECollisionType m_collisionType;
	EPhysicsLayer m_physicsLayer;

	float m_data1; //Radius or Width
	float m_data2; //Height
};

