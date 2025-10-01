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
	void LoadPlayerImage(const std::wstring& imagePath);

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

	inline int GetX() const { return static_cast<int>(m_posX); }
	inline int GetY() const { return static_cast<int>(m_posY); }
	inline bool HasImage() const { return m_playerImage != nullptr; }

private:
	double m_speed;

	Gdiplus::Bitmap* m_playerImage = nullptr;
	std::unordered_map<WPARAM, bool> m_keyStates; //키 상태 저장용 맵
};

