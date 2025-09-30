#include "pch.h"
#include "Background.h"


Background::Background(int windowWIdth, int windowHeight, const std::wstring& imagePath)
	: m_posX(0), m_posY(windowHeight), m_width(windowWIdth), m_height(windowHeight), m_backgroundImage(nullptr)
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
		graphics.DrawImage(m_backgroundImage, m_posX, m_posY, m_width, m_height);
	}
	else
	{
		Gdiplus::SolidBrush  blueBrush(Gdiplus::Color(255, 0, 0, 255)); // 이미지 미사용 시 파란색 배경
		graphics.FillRectangle(&blueBrush, m_posX, m_posY, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
}

void Background::Update()
{
	//시간마다 배경이 아래로 움직임
	m_posY += 1;

	//배경이 화면을 벗어나면 다시 위에서 시작
	if (m_posY >= m_height)
		m_posY = 0;
}