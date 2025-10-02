#include "pch.h"
#include "Component.h"

Component::Component(Actor* owner)

	: m_owner(owner)
{
}

void Component::Init()
{
}

void Component::Tick(float deltaSeconds)
{
}

void Component::Release()
{
	m_owner = nullptr;
}