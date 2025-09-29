#include "pch.h"
#include "PackMan.h"
#include "../Common.h"


PackMan::PackMan(int startX, int startY, int w, int h, int spd, float startAng, float sweepAng)
	: x(startX), y(startY), width(w), height(h), speed(spd), startAngle(startAng), sweepAngle(sweepAng)
{
}

void PackMan::Draw(Gdiplus::Graphics& graphics)
{
	Gdiplus::SolidBrush  yellowBrush(Gdiplus::Color(255, 255, 255, 0)); //����� �귯�� ��ü ���� (������, R, G, B)
	graphics.FillPie(&yellowBrush, x, y, width, height, startAngle, sweepAngle); //Ÿ�� ä��� (�귯��, x��ǥ, y��ǥ, �ʺ�, ����, ���۰���, ȣ�� ����)
}

void PackMan::MoveLeft()
{
	x -= speed;
	if (x < 0) 
		x = 0;

	startAngle = 210.0f;
	sweepAngle = 300.0f;
}

void PackMan::MoveRight()
{
	x += speed;

	if (x + width > WINDOW_WIDTH)
		x = WINDOW_WIDTH - width;

	startAngle = 30.0f;
	sweepAngle = 300.0f;
}

void PackMan::MoveUp()
{
	y -= speed;
	if (y < 0)
		y = 0;

	startAngle = 300.0f;
	sweepAngle = 300.0f;
}

void PackMan::MoveDown()
{
	y += speed;
	if (y + height > WINDOW_HEIGHT)
		y = WINDOW_HEIGHT - height;

	startAngle = 120.0f;
	sweepAngle = 300.0f;
}



