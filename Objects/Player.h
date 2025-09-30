#pragma once
#include <string>
#include <unordered_map>

namespace Gdiplus
{
	class Graphics;
	class Bitmap;
}

constexpr double PLAYER_DEFAULT_SPEED = 25.0;
constexpr int DEFAULT_PLAYER_IMAGE_SIZE = 48;

class AirPlayer
{
public:
	AirPlayer() = delete;
	explicit AirPlayer(const std::wstring& imagePath);

	~AirPlayer();

private:
	void ResetStartPosition();
	void LoadPlayerImage(const std::wstring& imagePath);

	void MoveLeft(double distance);
	void MoveRight(double distance);
	void MoveUp(double distance);
	void MoveDown(double distance);

public:
	void Render(Gdiplus::Graphics& graphics);
	void Update(double deltaSeconds);
	bool HandleInput(WPARAM wParam, bool isKeyDown);

	inline int GetX() const { return static_cast<int>(m_posX); }
	inline int GetY() const { return static_cast<int>(m_posY); }
	inline bool HasImage() const { return m_playerImage != nullptr; }

private:
	double m_posX;
	double m_posY;
	int m_width;
	int m_height;
	double m_speed;

	Gdiplus::Bitmap* m_playerImage = nullptr;
	std::unordered_map<WPARAM, bool> m_keyStates; //키 상태 저장용 맵
};

