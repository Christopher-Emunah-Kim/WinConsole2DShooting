#pragma once
#include "singleton.h"
#include "Service/TimeService.h"
#include "Service/ScreenService.h"

#include "Objects/Player.h"
#include "framework.h"

class GameMaster : public Singleton<GameMaster>
{
public:
	~GameMaster();

private:
	void InitializeGameObjects();
	void RenderActors();
	void ProcessDestroyPendingActors();

public:
	void RegisterActor(Actor* actor);
	void Initialize();
	void Release();

	void Tick(float deltaSeconds);
	void Render(HDC hdc);
	bool HandleInput(WPARAM wParam, bool isKeyDown);
	void SetUpWindow(HWND hwnd);

	void ReqeustDestroyActor(Actor* actor);
	
	inline const TimeService* GetTimeService() const { return m_timeService.get(); }

private:
	std::unique_ptr<TimeService> m_timeService;
	std::unique_ptr<ScreenService> m_screenService;
	std::unique_ptr<AirPlayer> m_airPlayer;

	std::map<ERenderLayer, std::set<Actor*>> m_actors;
	std::vector<Actor*> m_pendingDestroyActors;

	bool m_isInitialized = false;
};

