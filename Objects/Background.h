#pragma once
#include <string>

const std::wstring blockImagePath = L"./Images\\block.png";
constexpr int BLOCK_IMAGE_SIZE = 40;

class Background
{
public:
	Background() = delete;
	explicit Background(int windowWIdth, int windowHeight, const std::wstring& imagePath);

	~Background();

private:
	void LoadBackgroundImage(const std::wstring& imagePath);
	void LoadBlockImage(const std::wstring& imagePath);
public:
	void Render(Gdiplus::Graphics& graphics);
	void Update(double deltaSeconds);

private:
	int m_posX;
	int m_posY;

	int m_width;
	int m_height;

	Gdiplus::Bitmap* m_backgroundImage = nullptr;
	Gdiplus::Bitmap* m_blockImage = nullptr;
	double m_scrollAccumulator;

	double m_blockRowY;
	double m_blockSpeed;
	int m_emptyBlockIndex;
};

