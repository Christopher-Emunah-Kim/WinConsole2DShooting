#include "pch.h"
#include "Player.h"
#include "../Common.h"


AirPlayer::AirPlayer(int w, int h, int spd, const std::wstring& imagePath)
	: m_posX(0), m_posY(0), m_width(w), m_height(h), m_speed(spd), m_playerImage(nullptr)
{
	LoadPlayerImage(imagePath);
	ResetStartPosition();
}

AirPlayer::~AirPlayer()
{
	if (m_playerImage)
	{
		delete m_playerImage;
		m_playerImage = nullptr;
	}
}

void AirPlayer::Draw(Gdiplus::Graphics& graphics)
{
	if (m_playerImage)
	{
		graphics.DrawImage(m_playerImage, m_posX, m_posY, m_width, m_height);
	}
	else
	{
		Gdiplus::SolidBrush  yellowBrush(Gdiplus::Color(255, 255, 255, 0)); // 이미지 미사용 시 팩맨 모양 유지
		graphics.FillPie(&yellowBrush, m_posX, m_posY, m_width, m_height, 210, 300);
	}
}

void AirPlayer::MoveLeft()
{
	m_posX -= m_speed;

	if (m_posX < 0) 
		m_posX = 0;

}

void AirPlayer::MoveRight()
{
	m_posX += m_speed;

	if (m_posX + m_width > WINDOW_WIDTH)
		m_posX = WINDOW_WIDTH - m_width;

}

void AirPlayer::MoveUp()
{
	m_posY -= m_speed;

	if (m_posY < 0)
		m_posY = 0;
}

void AirPlayer::MoveDown()
{
	m_posY += m_speed;
	if (m_posY + m_height > WINDOW_HEIGHT)
		m_posY = WINDOW_HEIGHT - m_height;

}

void AirPlayer::ResetStartPosition()
{
	m_posX = (WINDOW_WIDTH - m_width) / 2;
	m_posY = (WINDOW_HEIGHT - m_height) / 2;
}

void AirPlayer::LoadPlayerImage(const std::wstring& imagePath)
{
	if(imagePath.empty())
		return;

	Gdiplus::Bitmap* loadedImage = Gdiplus::Bitmap::FromFile(imagePath.c_str());

	if(!loadedImage || loadedImage->GetLastStatus() != Gdiplus::Ok)
	{
		if(loadedImage)
			delete loadedImage;

		m_playerImage = nullptr;
		return;
	}

	if (loadedImage->GetWidth() > 0 && loadedImage->GetHeight() > 0)
	{
		m_width = loadedImage->GetWidth();
		m_height = loadedImage->GetHeight();
	}

	m_playerImage = loadedImage;
}



