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

public:
	void Initialize();

	void Tick();

	void Render();

	void Present(HDC hdc);

	bool HandleInput(WPARAM wParam, bool isKeyDown);

	void Release();

	void SetUpWindow(HWND hwnd);

	void SetRenderTargets(Gdiplus::Bitmap** backBuffer, Gdiplus::Graphics** backGraphics);

private:
	std::unique_ptr<TimeService> m_timeService;
	std::unique_ptr<ScreenService> m_screenService;
	std::unique_ptr<AirPlayer> m_airPlayer;
	std::unique_ptr<Background> m_background;

	bool m_isInitialized = false;
};

