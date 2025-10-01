#pragma once
#include "../framework.h"

class Actor
{
public:
	Actor();
	virtual ~Actor();

private:


public:
	virtual void Init() = 0;
	virtual void Tick(float deltaSeconds) = 0;
	virtual void Render(Gdiplus::Graphics& graphics) = 0;
	virtual void Release() = 0;

	void SetPosition(double x, double y);
	void SetSize(int width, int height);

	inline double GetX() const { return m_posX; }
	inline double GetY() const { return m_posY; }
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }

protected:
	double m_posX;
	double m_posY;

	int m_width;
	int m_height;

};

