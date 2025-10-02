#pragma once

class Actor;

class Component
{
public:
	Component(Actor* owner);
	virtual ~Component() = default;

	virtual void Init();
	virtual void Tick(float deltaSeconds);
	virtual void Release();

	inline Actor* GetOwner() const { return m_owner; }

private:
	Actor* m_owner = nullptr;
};

