#pragma once

#include <cstdint>
#include <array>
#include <vector>

using Block_t = uint8_t;

enum BlocksID
{
	DIRT,
	GRASS,
	STONE,
	COBBLESTONE,
	BEDROCK, 
	OAK_WOOD,
	OAK_LEAVES,
	SAND,
	SAND_STONE,
	AIR,

	NUM_TYPES
};

struct coords
{
	Block_t xTop, 
			yTop, 
			xSide, 
			ySide, 
			xBot, 
			yBot;
};

enum Facing
{
	UP, 
	RIGHT,
	LEFT,
	FORWARD, 
	BACKWARD,
	DOWN
};
