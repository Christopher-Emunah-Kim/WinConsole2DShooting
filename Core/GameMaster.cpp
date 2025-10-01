#include "pch.h"
#include "GameMaster.h"
#include "Objects/K_Actor.h"
#include "Objects/Background.h"
#include "ResourceManager.h"

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
	//Add ObjectType
	ResourceManager::GetInstance()->AddObjectType(EObjectType::Player);
	ResourceManager::GetInstance()->AddObjectType(EObjectType::BackGround_1);

	//Load All Image Resources
	ResourceManager::GetInstance()->LoadAllResources();

	//Generate Objects
	m_airPlayer = std::make_unique<AirPlayer>(EObjectType::Player);
	m_airPlayer->SetRenderLayer(ERenderLayer::Player);

	Background* background = new Background(WINDOW_WIDTH, WINDOW_HEIGHT, EObjectType::BackGround_1);
	background->SetRenderLayer(ERenderLayer::Background);

	//Add to Actor List
	AddActor(background);
}

void GameMaster::Release()
{
	for (size_t i = 0; i < m_actors.size(); ++i)
	{
		if (m_actors[i])
		{
			m_actors[i]->Release();

			delete m_actors[i];
			m_actors[i] = nullptr;
		}
	}

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

	m_screenService->ClearBackBuffer();

	RenderActors();

	m_screenService->RenderToScreen(hdc);
}

void GameMaster::RenderActors()
{
	Gdiplus::Graphics* backGraphics = m_screenService->GetBackGraphics();

	if (!backGraphics)
		return;

	//렌더링 순서에 따라 그리기
	for (ERenderLayer layer = ERenderLayer::Background; layer <= ERenderLayer::UI; layer = static_cast<ERenderLayer>(static_cast<int>(layer) + 1))
	{
		for (Actor* actor : m_actors)
		{
			if (actor && actor->GetRenderLayer() == layer)
			{
				actor->Render(*backGraphics);
			}
		}
		if (m_airPlayer && m_airPlayer->GetRenderLayer() == layer)
		{
			m_airPlayer->Render(*backGraphics);
		}
	}
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
