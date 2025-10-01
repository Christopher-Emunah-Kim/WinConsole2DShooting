#pragma once

class ScreenService
{
public:
	void Initialize(HWND hWnd);

	void RequestRender();

	void ClearBackBuffer();

	void Present(HDC hdc);
	
	void Release();

	inline Gdiplus::Graphics* GetBackGraphics() const { return m_backGraphics; }
	inline Gdiplus::Bitmap* GetBackBuffer() const { return m_backBuffer; }
	inline const HWND& GetHwnd() const { return m_hWnd; }

private:
	HWND m_hWnd = nullptr;
	Gdiplus::Bitmap* m_backBuffer = nullptr;
	Gdiplus::Graphics* m_backGraphics = nullptr;
};

