#pragma once
#include <string>
#include <unordered_map>

namespace Gdiplus
{
	class Graphics;
	class Bitmap;
}

constexpr int PLAYER_DEFAULT_SPEED = 25;
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

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

public:
	void Render(Gdiplus::Graphics& graphics);
	void Update();
	bool HandleInput(WPARAM wParam, bool isKeyDown);

	inline int GetX() const { return m_posX; }
	inline int GetY() const { return m_posY; }
	inline bool HasImage() const { return m_playerImage != nullptr; }

private:
	int m_posX;
	int m_posY;
	int m_width;
	int m_height;
	int m_speed;

	Gdiplus::Bitmap* m_playerImage = nullptr;
	std::unordered_map<WPARAM, bool> m_keyStates; //키 상태 저장용 맵
};

