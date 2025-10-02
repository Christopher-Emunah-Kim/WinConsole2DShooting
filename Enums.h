#pragma once

#include <cstdint>

enum class ERenderLayer : uint8_t
{
	Background,
	Default,
	Foreground,
	Actor,
	Player,
	Collision,
	UI,
	MaxLayers
};


enum class EObjectType
{
	Player,
	Enemy,
	Block,
	Bullet,
	Goal,
	BackGround_1,
	Background_2,
	Collision,
	number0,
	number1,
	number2,
	number3,
	number4,
	number5,
	number6,
	number7,
	number8,
	number9,
	MAX
};