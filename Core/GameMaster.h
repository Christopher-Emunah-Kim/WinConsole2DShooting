#pragma once
#include "singleton.h"
#include "Service/TimeService.h"
#include "Service/ScreenService.h"

#include "Objects/Player.h"
#include <memory>
#include <Windows.h>

class GameMaster : public Singleton<GameMaster>
{
public:
	~GameMaster();

private:
	void InitializeGameObjects();
	void AddActor(Actor* actor);
	void RenderActors();

public:
	void Initialize();
	void Release();

	void Tick(float deltaSeconds);
	void Render(HDC hdc);
	bool HandleInput(WPARAM wParam, bool isKeyDown);
	void SetUpWindow(HWND hwnd);

	const TimeService* GetTimeService() const { return m_timeService.get(); }

private:
	std::unique_ptr<TimeService> m_timeService;
	std::unique_ptr<ScreenService> m_screenService;
	std::unique_ptr<AirPlayer> m_airPlayer;
	std::vector<Actor*> m_actors;

	bool m_isInitialized = false;
};

