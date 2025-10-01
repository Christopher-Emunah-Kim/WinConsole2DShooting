#include "pch.h"
#include "K_Actor.h"
#include "../Core/ResourceManager.h"


Actor::Actor(EObjectType type)
	: m_position(), m_pivot(0.5f, 0.5f), m_width(0), m_height(0)
{
	m_image = ResourceManager::GetInstance()->GetImage(type, 0);
}

Actor::~Actor()
{
	Release();
}

void Actor::Init()
{
}

void Actor::Tick(float deltaSeconds)
{
	
}

void Actor::Render(Gdiplus::Graphics& graphics)
{
	if (m_image)
	{
		const int drawX = static_cast<int>(m_position.x - m_width * m_pivot.x);
		const int drawY = static_cast<int>(m_position.y - m_height * m_pivot.y);

		graphics.DrawImage(m_image, drawX, drawY, m_width, m_height);
	}
}

void Actor::Release()
{
	if (m_image)
	{
		delete m_image;
		m_image = nullptr;
	}
}

void Actor::LoadImage(const std::wstring& imagePath)
{
	if (imagePath.empty())
		return;

	Gdiplus::Bitmap* loadedImage = Gdiplus::Bitmap::FromFile(imagePath.c_str());

	if (!loadedImage || loadedImage->GetLastStatus() != Gdiplus::Ok)
	{
		if (loadedImage)
			delete loadedImage;
		m_image = nullptr;

		return;
	}

	m_width = loadedImage->GetWidth();
	m_height = loadedImage->GetHeight();

	m_image = loadedImage;
}



void Actor::SetPosition(float x, float y)
{
	m_position.x = x;
	m_position.y = y;
}

void Actor::SetPivot(float x, float y)
{
	m_pivot.x = x;
	m_pivot.y = y;
}

void Actor::SetSize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Actor::SetRenderLayer(ERenderLayer layer)
{ 
	targetLayer = layer; 
}

