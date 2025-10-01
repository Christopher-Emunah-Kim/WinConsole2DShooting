#pragma once
#include "Service/TimeService.h"
#include "Service/ScreenService.h"
#include "Objects/Background.h"
#include "Objects/Player.h"
#include <memory>
#include <Windows.h>

class GameMaster
{
public:
	GameMaster() = default;
	~GameMaster();

	GameMaster(const GameMaster&) = delete;
	GameMaster& operator=(const GameMaster&) = delete;
	GameMaster(GameMaster&&) = delete;
	GameMaster& operator=(GameMaster&&) = delete;
	
	//SIGNLETON PATTERN
	static GameMaster& GetInstance()
	{
		static GameMaster instance;
		return instance;
	}

public:
	void Initialize();
	void Release();

	void Tick(float deltaSeconds);
	void Render();
	void Present(HDC hdc);
	bool HandleInput(WPARAM wParam, bool isKeyDown);


	void SetUpWindow(HWND hwnd);

	const TimeService* GetTimeService() const { return m_timeService.get(); }

private:
	std::unique_ptr<TimeService> m_timeService;
	std::unique_ptr<ScreenService> m_screenService;
	std::unique_ptr<AirPlayer> m_airPlayer;
	std::unique_ptr<Background> m_background;

	std::vector<Actor*> m_actors;

	//Back Buffer
	Gdiplus::Bitmap* m_backBuffer = nullptr; //백버퍼용 GDI+ 비트맵 객체 포인터
	Gdiplus::Graphics* m_backGraphics = nullptr; //백버퍼용 GDI+ 그래픽 객체 포인터

	bool m_isInitialized = false;
};

