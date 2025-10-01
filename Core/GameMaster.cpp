#include "pch.h"
#include "GameMaster.h"
#include "../Objects/K_Actor.h"

GameMaster::~GameMaster()
{
	Release();
}

void GameMaster::Initialize()
{
	if(m_isInitialized)
		return;

	m_timeService = std::make_unique<TimeService>();
	m_screenService = std::make_unique<ScreenService>();
	
	m_timeService->Init();

	std::wstring playerImagePath = L"./Images\\player.png";
	std::wstring bgImagePath = L"./Images\\backGround_1.png";
	
	m_airPlayer = std::make_unique<AirPlayer>(playerImagePath);
	m_background = std::make_unique<Background>(WINDOW_WIDTH, WINDOW_HEIGHT, bgImagePath);

	m_isInitialized = true;
}

void GameMaster::Tick()
{
	if (!m_isInitialized || !m_timeService || !m_screenService)
		return;

	if (false == m_timeService->CanUpdate())
		return;

	const double deltaSeconds = static_cast<double>(m_timeService->GetDeltaSeconds());

	if (m_background)
	{
		m_background->Update(static_cast<float>(deltaSeconds));
	}
	if (m_airPlayer)
	{
		m_airPlayer->Tick(static_cast<float>(deltaSeconds));
	}

	m_screenService->RequestRender();
}

void GameMaster::Render()
{
	if(!m_screenService)
		return;

	Gdiplus::Graphics* backGraphics = m_screenService->GetBackGraphics();

	if (!backGraphics)
		return;

	m_screenService->ClearBackBuffer();

	if(m_background)
		m_background->Render(*backGraphics);

	if(m_airPlayer)
		m_airPlayer->Render(*backGraphics);
}

void GameMaster::Present(HDC hdc)
{
	if(!m_screenService)
		return;

	m_screenService->Present(hdc);
}

bool GameMaster::HandleInput(WPARAM wParam, bool isKeyDown)
{
	if(!m_airPlayer)
		return false;

	const bool handled = m_airPlayer->HandleInput(wParam, isKeyDown);

	if(handled && m_screenService)
	{
		m_screenService->RequestRender();
	}

	return handled;
}

void GameMaster::SetUpWindow(HWND hwnd)
{
	if(!m_screenService)
		return;

	m_screenService->Initialize(hwnd);
}

void GameMaster::SetRenderTargets(Gdiplus::Bitmap** backBuffer, Gdiplus::Graphics** backGraphics)
{
	if (m_screenService)
	{
		m_screenService->SetRenderTargets(backBuffer, backGraphics);
	}
}

void GameMaster::Release()
{
	if (m_airPlayer)
	{
		m_airPlayer.reset();
	}
	if (m_background)
	{
		m_background.reset();
	}
	if (m_screenService)
	{
		m_screenService.reset();
	}
	if (m_timeService)
	{
		m_timeService.reset();
	}

	m_isInitialized = false;
}
