#pragma once

#include <cstdint>

enum class ERenderLayer : uint8_t
{
	Background,
	Default,
	Foreground,
	Actor,
	Player,
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
	MAX
};