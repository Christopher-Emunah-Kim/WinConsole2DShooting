#include "pch.h"
#include "Player.h"
#include "../Common.h"
#include "Background.h"
#include "../Core/GameMaster.h"


AirPlayer::AirPlayer(const std::wstring& imagePath)
	: m_posX(0.0), m_posY(0.0), m_width(0), m_height(0), m_speed(PLAYER_DEFAULT_SPEED), m_playerImage(nullptr)
{
	m_keyStates.clear();

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

void AirPlayer::Render(Gdiplus::Graphics& graphics)
{
	if (m_playerImage)
	{
		graphics.DrawImage(m_playerImage, static_cast<int>(m_posX), static_cast<int>(m_posY), m_width, m_height);
	}
	else
	{
		Gdiplus::SolidBrush  yellowBrush(Gdiplus::Color(255, 255, 255, 0)); // 이미지 미사용 시 팩맨 모양 유지
		graphics.FillPie(&yellowBrush, m_posX, m_posY, m_width, m_height, 210, 300);
	}
}

void AirPlayer::Update(double deltaSeconds)
{
	if(deltaSeconds <= 0.0)
		return;

	const double moveDistance = m_speed * deltaSeconds;

	if (m_keyStates['A'] || m_keyStates[VK_LEFT])
	{
		MoveLeft(moveDistance);
	}

	if (m_keyStates['D'] || m_keyStates[VK_RIGHT])
	{
		MoveRight(moveDistance);
	}

	if (m_keyStates['W'] || m_keyStates[VK_UP])
	{
		MoveUp(moveDistance);
	}

	if (m_keyStates['S'] || m_keyStates[VK_DOWN])
	{
		MoveDown(moveDistance);
	}
}

bool AirPlayer::HandleInput(WPARAM wParam, bool isKeyDown)
{
	switch (wParam)
	{
	case 'A':
	case VK_LEFT:
	case 'D':
	case VK_RIGHT:
	case 'W':
	case VK_UP:
	case 'S':
	case VK_DOWN:
		m_keyStates[wParam] = isKeyDown;
		return true;
	default:
		break;
	}

	return false;
}

void AirPlayer::MoveLeft(double distance)
{
	m_posX -= distance;

	//왼쪽 테두리에 도달하면 오른쪽에서 재등장
	if (m_posX < 0.0)
	{
		m_posX = WINDOW_WIDTH - m_width;
	}
}

void AirPlayer::MoveRight(double distance)
{
	m_posX += distance;

	//벽을 넘어가면 다시 왼쪽에서 시작
	if (m_posX + m_width > WINDOW_WIDTH)
	{
		m_posX = 0.0;
	}
}

void AirPlayer::MoveUp(double distance)
{
	m_posY -= distance;

	if (m_posY < 0.0)
		m_posY = 0.0;
}

void AirPlayer::MoveDown(double distance)
{
	m_posY += distance;

	if (m_posY + m_height > WINDOW_HEIGHT)
		m_posY = WINDOW_HEIGHT - m_height;

}

void AirPlayer::ResetStartPosition()
{
	m_posX = (WINDOW_WIDTH - m_width) / 2;
	m_posY = (WINDOW_HEIGHT - m_height) / 2 + 150.0;
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

	m_width = DEFAULT_PLAYER_IMAGE_SIZE;
	m_height = DEFAULT_PLAYER_IMAGE_SIZE;

	/*if (loadedImage->GetWidth() > 0 && loadedImage->GetHeight() > 0)
	{
		m_width = loadedImage->GetWidth();
		m_height = loadedImage->GetHeight();
	}*/

	m_playerImage = loadedImage;
}



