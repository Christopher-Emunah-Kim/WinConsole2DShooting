#pragma once
#include <string>

namespace Gdiplus
{
	class Graphics;
	class Bitmap;
}


class AirPlayer
{
public:
	AirPlayer(int w, int h, int spd, const std::wstring& imagePath);
	~AirPlayer();

private:


public:
	void Draw(Gdiplus::Graphics& graphics);

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	void ResetStartPosition();
	void LoadPlayerImage(const std::wstring& imagePath);

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
};

