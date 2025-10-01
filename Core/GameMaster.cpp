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
	m_airPlayer = std::make_unique<AirPlayer>(L"./Images\\player.png");
	
	m_timeService->Init();

	m_isInitialized = true;
}

void GameMaster::Release()
{
	if (m_airPlayer)
	{
		m_airPlayer.reset();
	}
	if (m_screenService)
	{
		m_screenService->Release();
		m_screenService.reset();
	}
	if (m_timeService)
	{
		m_timeService.reset();
	}

	m_isInitialized = false;

	for(size_t i = 0; i < m_actors.size(); ++i)
	{
		if(m_actors[i])
		{
			m_actors[i]->Release();

			delete m_actors[i];
			m_actors[i] = nullptr;
		}
	}
}


void GameMaster::Tick(float deltaSeconds)
{
	if (!m_isInitialized || !m_timeService || !m_screenService)
		return;

	if (false == m_timeService->CanUpdate())
		return;

	for(Actor* actor : m_actors)
	{
		if(actor)
			actor->Tick(deltaSeconds);
	}
	
	if (m_airPlayer)
	{
		m_airPlayer->Tick(deltaSeconds);
	}

	m_screenService->RequestRender();
}

void GameMaster::Render(HDC hdc)
{
	if(!m_screenService)
		return;

	Gdiplus::Graphics* backGraphics = m_screenService->GetBackGraphics();

	if (!backGraphics)
		return;

	m_screenService->ClearBackBuffer();

	for (Actor* actor : m_actors)
	{
		if (actor)
			actor->Render(*backGraphics);
	}

	if(m_airPlayer)
		m_airPlayer->Render(*backGraphics);

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

void GameMaster::AddActor(Actor* actor)
{
	if(actor)
		m_actors.push_back(actor);
}
