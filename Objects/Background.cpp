#include "pch.h"
#include "Background.h"


Background::Background(int windowWIdth, int windowHeight, const std::wstring& imagePath)
	: m_posX(0), m_posY(0), m_width(windowWIdth), m_height(windowHeight), m_backgroundImage(nullptr), m_scrollAccumulator(0.0)
{
	LoadBackgroundImage(imagePath);
}

Background::~Background()
{
	if (m_backgroundImage)
	{
		delete m_backgroundImage;
		m_backgroundImage = nullptr;
	}
}


void Background::LoadBackgroundImage(const std::wstring& imagePath)
{
	if(imagePath.empty())
		return;

	Gdiplus::Bitmap* loadedImage = Gdiplus::Bitmap::FromFile(imagePath.c_str());

	if(!loadedImage || loadedImage->GetLastStatus() != Gdiplus::Ok)
	{
		if(loadedImage)
			delete loadedImage;
		m_backgroundImage = nullptr;
		return;
	}
	m_backgroundImage = loadedImage;
}

void Background::Render(Gdiplus::Graphics& graphics)
{
	if (m_backgroundImage)
	{
		const int y0 = m_posY;
		const int y1 = m_posY - m_height;

		graphics.DrawImage(m_backgroundImage, m_posX, y0, m_width, m_height);
		graphics.DrawImage(m_backgroundImage, m_posX, y1, m_width, m_height);

		if (m_height < WINDOW_HEIGHT)
		{
			const int y2 = m_posY + m_height;
			graphics.DrawImage(m_backgroundImage, m_posX, y2, m_width, m_height);
		}
	}
	else
	{
		Gdiplus::SolidBrush  blueBrush(Gdiplus::Color(255, 0, 0, 255)); // 이미지 미사용 시 파란색 배경
		graphics.FillRectangle(&blueBrush, m_posX, m_posY, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
}

void Background::Update(double deltaSeconds)
{
	constexpr double SCROLL_SPEED = 120.0;

	m_scrollAccumulator += deltaSeconds * SCROLL_SPEED; //스크롤 속도 조절

	const int scrollPixels = static_cast<int>(m_scrollAccumulator);

	if (scrollPixels <= 0)
	{
		return;
	}

	m_scrollAccumulator -= scrollPixels;

	m_posY = (m_posY + scrollPixels) % m_height;

	if(m_posY < 0)
		m_posY += m_height;

}