#pragma once

class ScreenService
{
public:
	void Initialize(HWND hWnd);

	void SetRenderTargets(Gdiplus::Bitmap** backBuffer, Gdiplus::Graphics** backGraphics);

	void RequestRender();

	void ClearBackBuffer();

	void Present(HDC hdc);

	inline Gdiplus::Graphics* GetBackGraphics() const { return m_backGraphics; }
	inline Gdiplus::Bitmap* GetBackBuffer() const { return m_backBuffer; }

private:
	HWND m_hWnd = nullptr;
	Gdiplus::Bitmap* m_backBuffer = nullptr;
	Gdiplus::Graphics* m_backGraphics = nullptr;
};

