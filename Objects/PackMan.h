#pragma once

class PackMan
{
public:
	PackMan(int startX, int startY, int w, int h, int spd, float startAng, float sweepAng);
	~PackMan() = default;

private:


public:
	void Draw(Gdiplus::Graphics& graphics);

	void MoveLeft();
	void MoveRight();
	void MoveUp();
	void MoveDown();

	inline int GetX() const { return x; }
	inline int GetY() const { return y; }

private:
	int x;
	int y;
	int width;
	int height;
	int speed;
	float startAngle;
	float sweepAngle;
};

