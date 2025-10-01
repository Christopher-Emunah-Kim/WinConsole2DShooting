#include "pch.h"
#include "Background.h"
#include <cmath>


Background::Background(int windowWIdth, int windowHeight, EObjectType type)
	: Actor(type),m_blockImage(nullptr), m_scrollAccumulator(0.0), 
	m_blockRowY(0.0), m_blockSpeed(120.0), m_emptyBlockIndex(-1)
{
	m_width = windowWIdth;
	m_height = windowHeight;

	Init();
}

void Background::Init()
{
	Actor::Init();

	LoadBlockImage(blockImagePath);

	if (m_blockImage)
	{
		m_blockRowY = -static_cast<double>(m_blockImage->GetHeight());
		const int widthCount = WINDOW_WIDTH / m_blockImage->GetWidth() + 2;
		m_emptyBlockIndex = (widthCount > 0) ? (rand() % widthCount) : -1;
	}
}

Background::~Background()
{
	Release();
}

void Background::LoadBlockImage(const std::wstring& imagePath)
{
	if(imagePath.empty())
		return;

	Gdiplus::Bitmap* loadedImage = Gdiplus::Bitmap::FromFile(imagePath.c_str());

	if(!loadedImage || loadedImage->GetLastStatus() != Gdiplus::Ok)
	{
		if(loadedImage)
			delete loadedImage;
		m_blockImage = nullptr;
		return;
	}

	m_blockImage = loadedImage;
}


void Background::Tick(float deltaSeconds)
{
	Actor::Tick(deltaSeconds);

	constexpr double SCROLL_SPEED = 120.0;

	m_scrollAccumulator += deltaSeconds * SCROLL_SPEED; //스크롤 속도 조절

	const int scrollPixels = static_cast<int>(m_scrollAccumulator);

	if (scrollPixels > 0)
	{
		m_scrollAccumulator -= scrollPixels;

		//m_posY = static_cast<int>(m_posY + scrollPixels) % m_height;
		m_position.y = std::fmod(m_position.y + scrollPixels, static_cast<double>(m_height));

		if (m_position.y < 0)
			m_position.y += m_height;
	}

	if (m_blockImage)
	{
		m_blockRowY += m_blockSpeed * deltaSeconds;

		const int imageHeight = m_blockImage->GetHeight();

		if (m_blockRowY > WINDOW_HEIGHT)
		{
			m_blockRowY = -static_cast<double>(imageHeight);

			const int widthCount = WINDOW_WIDTH / m_blockImage->GetWidth() + 2;
			m_emptyBlockIndex = (widthCount > 0) ? (rand() % widthCount) : -1;
		}
	}
}

void Background::Render(Gdiplus::Graphics& graphics)
{
	if (m_image)
	{
		const float y0 = m_position.y;
		const float y1 = m_position.y - m_height;

		graphics.DrawImage(m_image, static_cast<int>(m_position.x), static_cast<int>(y0), m_width, m_height);
		graphics.DrawImage(m_image, static_cast<int>(m_position.x), static_cast<int>(y1), m_width, m_height);

		if (m_height < WINDOW_HEIGHT)
		{
			const float y2 = m_position.y + m_height;
			graphics.DrawImage(m_image, static_cast<int>(m_position.x), static_cast<int>(y2), m_width, m_height);
		}
	}

	if (m_blockImage)
	{
		int imageHeight = BLOCK_IMAGE_SIZE;
		int imageWidth = BLOCK_IMAGE_SIZE;

		int widthCount = WINDOW_WIDTH / imageWidth + 2;

		const int y = static_cast<int>(m_blockRowY);


		if(y + imageHeight >= 0 && y <= WINDOW_HEIGHT)
		{
			for (int i = 0; i < widthCount; ++i)
			{
				if(i == m_emptyBlockIndex)
					continue;

				const int x = i * imageWidth;
				graphics.DrawImage(m_blockImage, x, y, imageWidth, imageHeight);
			}
		}
	}
}

void Background::Release()
{
	Actor::Release();

	if (m_blockImage)
	{
		delete m_blockImage;
		m_blockImage = nullptr;
	}
}
