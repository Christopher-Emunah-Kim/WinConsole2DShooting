#include "pch.h"
#include "PackMan.h"
#include "../Common.h"


PackMan::PackMan(int startX, int startY, int w, int h, int spd, float startAng, float sweepAng)
	: x(startX), y(startY), width(w), height(h), speed(spd), startAngle(startAng), sweepAngle(sweepAng)
{
}

void PackMan::Draw(Gdiplus::Graphics& graphics)
{
	Gdiplus::SolidBrush  yellowBrush(Gdiplus::Color(255, 255, 255, 0)); //노란색 브러시 객체 생성 (불투명도, R, G, B)
	graphics.FillPie(&yellowBrush, x, y, width, height, startAngle, sweepAngle); //타원 채우기 (브러시, x좌표, y좌표, 너비, 높이, 시작각도, 호의 각도)
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



