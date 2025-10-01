#pragma once
#include "../framework.h"

class Actor
{
public:
	Actor() = delete;
	explicit Actor(const std::wstring& imagePath);
	virtual ~Actor();

private:
	void LoadImage(const std::wstring& imagePath);

public:
	virtual void Init();
	virtual void Tick(float deltaSeconds);
	virtual void Render(Gdiplus::Graphics& graphics);
	virtual void Release();

	void SetPosition(float x, float y);
	void SetPivot(float x, float y);
	void SetSize(int width, int height);

	inline const Position& GetPosition() const { return m_position; }
	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }

protected:
	Position m_position;
	Position m_pivot;

	int m_width;
	int m_height;

	Gdiplus::Bitmap* m_image;
};

