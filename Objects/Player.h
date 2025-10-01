#pragma once
#include "K_Actor.h"
#include <string>
#include <unordered_map>

namespace Gdiplus
{
	class Graphics;
	class Bitmap;
}

constexpr double PLAYER_DEFAULT_SPEED = 150.0;
constexpr int DEFAULT_PLAYER_IMAGE_SIZE = 48;

class AirPlayer : public Actor
{
public:
	AirPlayer() = delete;
	explicit AirPlayer(const std::wstring& imagePath);

	virtual ~AirPlayer();

private:
	void ResetStartPosition();

	void MoveLeft(double distance);
	void MoveRight(double distance);
	void MoveUp(double distance);
	void MoveDown(double distance);

public:
	virtual void Init() override;
	virtual void Tick(float deltaSeconds) override;
	virtual void Render(Gdiplus::Graphics& graphics) override;
	virtual void Release() override;

	bool HandleInput(WPARAM wParam, bool isKeyDown);

	inline float GetX() const { return m_position.x; }
	inline float GetY() const { return m_position.y; }

private:
	double m_speed;

	std::unordered_map<WPARAM, bool> m_keyStates; //키 상태 저장용 맵
};

