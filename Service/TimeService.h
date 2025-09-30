#pragma once
#include <chrono>

using namespace std::chrono;

using TimePoint = steady_clock::time_point;

static constexpr int FPS = 60;
static constexpr float TICK_INTERVAL_MS = 1000.0f / (float)FPS - 0.1f;

class TimeService
{
public:
	void Init();
	bool CanUpdate();
	
	float GetDeltaSeconds() const { return m_lastDeltaSeconds; }

private:
	TimePoint m_prevTimePoint{};
	float m_lastDeltaSeconds = 0.0f;
};

