#include "pch.h"
#include "ScreenService.h"

void ScreenService::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;

	//백버퍼용 GDI+ 비트맵 객체 생성
	if (m_backBuffer == nullptr)
	{
		m_backBuffer = new Gdiplus::Bitmap(WINDOW_WIDTH, WINDOW_HEIGHT, PixelFormat32bppARGB);
	}
	//백버퍼용 GDI+ 그래픽 객체 생성
	if (m_backGraphics == nullptr && m_backBuffer != nullptr)
	{
		m_backGraphics = Gdiplus::Graphics::FromImage(m_backBuffer);
	}

	if (!m_backGraphics) //백버퍼용 그래픽 객체 생성 실패시
	{
		MessageBox(hWnd, L"Back Buffer Graphics Create Failed!", L"Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(0); //프로그램 종료
	}
}

void ScreenService::Release()
{
	if (m_backGraphics)
	{
		delete m_backGraphics;
		m_backGraphics = nullptr;
	}
	if (m_backBuffer)
	{
		delete m_backBuffer;
		m_backBuffer = nullptr;
	}
	m_hWnd = nullptr;
}


void ScreenService::RequestRender()
{
	if (m_hWnd)
	{
		InvalidateRect(m_hWnd, nullptr, FALSE); //윈도우 전체 영역을 무효화하여 다시 그리기
	}
}

void ScreenService::ClearBackBuffer()
{
	if (m_backGraphics && m_backBuffer)
	{
		m_backGraphics->Clear(Gdiplus::Color(255, 255, 255, 255));
	}
}


void ScreenService::Present(HDC hdc)
{
	if (!hdc)
	{
		return;
	}

	Gdiplus::Bitmap* backBuffer = GetBackBuffer();

	if (!backBuffer)
	{
		return;
	}

	Gdiplus::Graphics graphics(hdc);
	graphics.DrawImage(backBuffer, 0, 0);
}