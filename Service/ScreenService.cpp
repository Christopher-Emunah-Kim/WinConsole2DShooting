#include "pch.h"
#include "ScreenService.h"

void ScreenService::Initialize(HWND hWnd)
{
	m_hWnd = hWnd;

	//����ۿ� GDI+ ��Ʈ�� ��ü ����
	if (m_backBuffer == nullptr)
	{
		m_backBuffer = new Gdiplus::Bitmap(WINDOW_WIDTH, WINDOW_HEIGHT, PixelFormat32bppARGB);
	}
	//����ۿ� GDI+ �׷��� ��ü ����
	if (m_backGraphics == nullptr && m_backBuffer != nullptr)
	{
		m_backGraphics = Gdiplus::Graphics::FromImage(m_backBuffer);
	}

	if (!m_backGraphics) //����ۿ� �׷��� ��ü ���� ���н�
	{
		MessageBox(hWnd, L"Back Buffer Graphics Create Failed!", L"Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(0); //���α׷� ����
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