#pragma once
#include "Service/TimeService.h"
#include "Service/ScreenService.h"
#include <memory>

class GameMaster
{
private:
	void Update();

public:
	void Initialize();

	void Tick();

	void Render(Gdiplus::Graphics& graphics);

private:
	std::unique_ptr<TimeService> m_timeService;
	std::unique_ptr<ScreenService> m_screenService;
};

