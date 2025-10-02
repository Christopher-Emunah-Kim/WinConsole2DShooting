#pragma once
#include "K_Actor.h"
#include <string>

const std::wstring blockImagePath = L"./Images\\block.png";
constexpr int BLOCK_IMAGE_SIZE = 40;

class Background : public Actor
{
public:
	Background() = delete;
	explicit Background(EObjectType type);

	~Background();

private:
	void LoadBlockImage(const std::wstring& imagePath);
public:
	virtual void Init() override;
	virtual void Tick(float deltaSeconds) override;
	virtual void Render(Gdiplus::Graphics& graphics) override;
	virtual void Release() override;
	virtual void OverlapWith(Actor* other) override;


private:
	Gdiplus::Bitmap* m_blockImage = nullptr;
	double m_scrollAccumulator;
	double m_blockRowY;
	double m_blockSpeed;
	int m_emptyBlockIndex;
};

