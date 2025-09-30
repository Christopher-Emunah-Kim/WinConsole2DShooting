#include "pch.h"
#include "GameMaster.h"

void GameMaster::Initialize()
{
	m_timeService = std::make_unique<TimeService>();
	m_screenService = std::make_unique<ScreenService>();
}

void GameMaster::Tick()
{
	if(!m_timeService || !m_screenService)
		return;

	m_timeService->Init();

	Update();

	m_screenService->RequestRender();
}

void GameMaster::Render(Gdiplus::Graphics& graphics)
{

}

void GameMaster::Update()
{
}
