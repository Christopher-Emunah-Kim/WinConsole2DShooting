#pragma once
#include <string>

class Background
{
public:
	Background() = delete;
	explicit Background(int windowWIdth, int windowHeight, const std::wstring& imagePath);

	~Background();

private:
	void LoadBackgroundImage(const std::wstring& imagePath);
public:
	void Render(Gdiplus::Graphics& graphics);
	void Update(double deltaSeconds);

private:
	int m_posX;
	int m_posY;
	int m_width;
	int m_height;
	Gdiplus::Bitmap* m_backgroundImage = nullptr;
	double m_scrollAccumulator = 0.0;
};

