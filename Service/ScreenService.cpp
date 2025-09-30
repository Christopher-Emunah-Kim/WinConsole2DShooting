#include "pch.h"
#include "ScreenService.h"

void ScreenService::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;
}

void ScreenService::SetRenderTargets(Gdiplus::Bitmap** backBuffer, Gdiplus::Graphics** backGraphics)
{
	if (backBuffer)
		m_backBuffer = *backBuffer;
	if (backGraphics)
		m_backGraphics = *backGraphics;
}

void ScreenService::RequestRender()
{
	if (m_hWnd)
	{
		InvalidateRect(m_hWnd, nullptr, FALSE); //������ ��ü ������ ��ȿȭ�Ͽ� �ٽ� �׸���
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