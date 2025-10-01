#include "pch.h"
#include "Player.h"
#include "Background.h"
#include "../Core/GameMaster.h"


AirPlayer::AirPlayer(const std::wstring& imagePath)
	: Actor(imagePath), m_speed(PLAYER_DEFAULT_SPEED)
{
	m_keyStates.clear();

	ResetStartPosition();

	SetSize(DEFAULT_PLAYER_IMAGE_SIZE, DEFAULT_PLAYER_IMAGE_SIZE);
}

AirPlayer::~AirPlayer()
{
	Release();
}

void AirPlayer::Render(Gdiplus::Graphics& graphics)
{
	Actor::Render(graphics);
	
}

void AirPlayer::Release()
{
	Actor::Release();
}

void AirPlayer::Init()
{
	Actor::Init();
}

void AirPlayer::Tick(float deltaSeconds)
{
	Actor::Tick(deltaSeconds);

	if (deltaSeconds <= 0.0)
		return;

	const float moveDistance = m_speed * deltaSeconds;

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

void AirPlayer::MoveLeft(float distance)
{
	m_position.x -= distance;

	//왼쪽 테두리에 도달하면 오른쪽에서 재등장
	if (m_position.x < 0.0)
	{
		m_position.x = static_cast<float>(WINDOW_WIDTH - m_width);
	}
}

void AirPlayer::MoveRight(float distance)
{
	m_position.x += distance;

	//벽을 넘어가면 다시 왼쪽에서 시작
	if (m_position.x + m_width > WINDOW_WIDTH)
	{
		m_position.x = 0.0;
	}
}

void AirPlayer::MoveUp(float distance)
{
	m_position.y -= distance;

	if (m_position.y < 0.0)
		m_position.y = 0.0;
}

void AirPlayer::MoveDown(float distance)
{
	m_position.y += distance;

	if (m_position.y + m_height > WINDOW_HEIGHT)
		m_position.y = static_cast<float>(WINDOW_HEIGHT - m_height);

}

void AirPlayer::ResetStartPosition()
{
	m_position.x = static_cast<float>((WINDOW_WIDTH - m_width) / 2);
	m_position.y = (WINDOW_HEIGHT - m_height) / 2 + 150.0f;
}
