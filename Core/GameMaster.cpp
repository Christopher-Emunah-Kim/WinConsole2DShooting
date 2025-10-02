#include "pch.h"
#include "GameMaster.h"
#include "Objects/K_Actor.h"
#include "Objects/Background.h"
#include "ResourceManager.h"
#include "ActorFactory.h"

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

	InitializeGameObjects();

	m_timeService->Init();

	m_isInitialized = true;
}

void GameMaster::InitializeGameObjects()
{
	ResourceManager::GetInstance()->Initialize();

	//Generate Objects
	m_airPlayer = std::make_unique<AirPlayer>(EObjectType::Player);
	m_airPlayer->SetRenderLayer(ERenderLayer::Player);

	//일반 Actor들은 Factory클래스 사용
	Factory::GetInstance()->SpawnActor<Background>(EObjectType::BackGround_1, ERenderLayer::Background);
}

void GameMaster::Release()
{
	ProcessDestroyPendingActors();

	for(auto& layerset : m_actors)
	{
		for(Actor* actor : layerset.second)
		{
			if(actor)
			{
				actor->Release();
				delete actor;
				actor = nullptr;
			}
		}
		layerset.second.clear();
	}
	m_actors.clear();

	ResourceManager::GetInstance()->ReleaseAllResources();

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

	m_pendingDestroyActors.clear();
}


void GameMaster::Tick(float deltaSeconds)
{
	if (!m_isInitialized || !m_timeService || !m_screenService)
		return;

	if (false == m_timeService->CanUpdate())
		return;

	for(const auto& layerPair : m_actors)
	{
		for(Actor* actor : layerPair.second)
		{
			if(actor)
				actor->Tick(deltaSeconds);
		}
	}
	
	if (m_airPlayer)
	{
		m_airPlayer->Tick(deltaSeconds);
	}

	m_screenService->RequestRender();

	ProcessDestroyPendingActors();
}

void GameMaster::Render(HDC hdc)
{
	if(!m_screenService)
		return;

	m_screenService->ClearBackBuffer();

	RenderActors();

	m_screenService->RenderToScreen(hdc);
}

void GameMaster::RenderActors()
{
	Gdiplus::Graphics* backGraphics = m_screenService->GetBackGraphics();

	if (!backGraphics)
		return;

	//map키가 이미 레이어순 정렬되어있으므로 순회하면서 Render
	for (const auto& layerPair : m_actors)
	{
		for (Actor* actor : layerPair.second)
		{
			if (actor)
				actor->Render(*backGraphics);
		}
	}

	//플레이어는 최상단에.
	if (m_airPlayer)
	{
		m_airPlayer->Render(*backGraphics);
	}
}

void GameMaster::ProcessDestroyPendingActors()
{
	if (m_pendingDestroyActors.empty())
		return;

	for(Actor* actor : m_pendingDestroyActors)
	{
		if(!actor)
			continue;

		const ERenderLayer layer = actor->GetRenderLayer();

		auto& layerset = m_actors[layer];
		layerset.erase(actor);

		if (layerset.empty())
		{
			m_actors.erase(layer);
		}
		
		delete actor;
		actor = nullptr;
	}

	m_pendingDestroyActors.clear();
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

void GameMaster::ReqeustDestroyActor(Actor* actor)
{
	if (actor)
		m_pendingDestroyActors.push_back(actor);
}

void GameMaster::RegisterActor(Actor* actor)
{
	if(actor)
		m_actors[actor->GetRenderLayer()].insert(actor);
}
