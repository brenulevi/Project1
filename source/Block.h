#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

using namespace glm;

enum BlockType
{
	AIR,
	GRASS,
	DIRT,
	STONE,
	SAND,
	WATER,
	BEDROCK
};

class Block
{
public:
	vec3 m_position;
	BlockType m_type;
};

namespace BlockData
{
	static vec2 topUv[] =
	{
		// GRASS
		vec2(0.0f / 16.0f, 15.0f / 16.0f),
		vec2(1.0f / 16.0f, 15.0f / 16.0f),
		vec2(1.0f / 16.0f, 16.0f / 16.0f),
		vec2(0.0f / 16.0f, 16.0f / 16.0f),

		// DIRT
		vec2(2.0f / 16.0f, 15.0f / 16.0f),
		vec2(3.0f / 16.0f, 15.0f / 16.0f),
		vec2(3.0f / 16.0f, 16.0f / 16.0f),
		vec2(2.0f / 16.0f, 16.0f / 16.0f),

		// STONE
		vec2(3.0f / 16.0f, 15.0f / 16.0f),
		vec2(4.0f / 16.0f, 15.0f / 16.0f),
		vec2(4.0f / 16.0f, 16.0f / 16.0f),
		vec2(3.0f / 16.0f, 16.0f / 16.0f),

		// SAND
		vec2(4.0f / 16.0f, 15.0f / 16.0f),
		vec2(5.0f / 16.0f, 15.0f / 16.0f),
		vec2(5.0f / 16.0f, 16.0f / 16.0f),
		vec2(4.0f / 16.0f, 16.0f / 16.0f),

		// WATER
		vec2(5.0f / 16.0f, 15.0f / 16.0f),
		vec2(6.0f / 16.0f, 15.0f / 16.0f),
		vec2(6.0f / 16.0f, 16.0f / 16.0f),
		vec2(5.0f / 16.0f, 16.0f / 16.0f),

		// BEDROCK
		vec2(15.0f / 16.0f, 15.0f / 16.0f),
		vec2(16.0f / 16.0f, 15.0f / 16.0f),
		vec2(16.0f / 16.0f, 16.0f / 16.0f),
		vec2(15.0f / 16.0f, 16.0f / 16.0f),
	};

	static vec2 bottomUv[] =
	{
		// GRASS
		vec2(2.0f / 16.0f, 15.0f / 16.0f),
		vec2(3.0f / 16.0f, 15.0f / 16.0f),
		vec2(3.0f / 16.0f, 16.0f / 16.0f),
		vec2(2.0f / 16.0f, 16.0f / 16.0f),

		// DIRT
		vec2(2.0f / 16.0f, 15.0f / 16.0f),
		vec2(3.0f / 16.0f, 15.0f / 16.0f),
		vec2(3.0f / 16.0f, 16.0f / 16.0f),
		vec2(2.0f / 16.0f, 16.0f / 16.0f),

		// STONE
		vec2(3.0f / 16.0f, 15.0f / 16.0f),
		vec2(4.0f / 16.0f, 15.0f / 16.0f),
		vec2(4.0f / 16.0f, 16.0f / 16.0f),
		vec2(3.0f / 16.0f, 16.0f / 16.0f),

		// SAND
		vec2(4.0f / 16.0f, 15.0f / 16.0f),
		vec2(5.0f / 16.0f, 15.0f / 16.0f),
		vec2(5.0f / 16.0f, 16.0f / 16.0f),
		vec2(4.0f / 16.0f, 16.0f / 16.0f),

		// WATER
		vec2(5.0f / 16.0f, 15.0f / 16.0f),
		vec2(6.0f / 16.0f, 15.0f / 16.0f),
		vec2(6.0f / 16.0f, 16.0f / 16.0f),
		vec2(5.0f / 16.0f, 16.0f / 16.0f),

		// BEDROCK
		vec2(15.0f / 16.0f, 15.0f / 16.0f),
		vec2(16.0f / 16.0f, 15.0f / 16.0f),
		vec2(16.0f / 16.0f, 16.0f / 16.0f),
		vec2(15.0f / 16.0f, 16.0f / 16.0f),
	};

	static vec2 rightUv[] =
	{
		// GRASS
		vec2(1.0f / 16.0f, 15.0f / 16.0f),
		vec2(2.0f / 16.0f, 15.0f / 16.0f),
		vec2(2.0f / 16.0f, 16.0f / 16.0f),
		vec2(1.0f / 16.0f, 16.0f / 16.0f),

		// DIRT
		vec2(2.0f / 16.0f, 15.0f / 16.0f),
		vec2(3.0f / 16.0f, 15.0f / 16.0f),
		vec2(3.0f / 16.0f, 16.0f / 16.0f),
		vec2(2.0f / 16.0f, 16.0f / 16.0f),

		// STONE
		vec2(3.0f / 16.0f, 15.0f / 16.0f),
		vec2(4.0f / 16.0f, 15.0f / 16.0f),
		vec2(4.0f / 16.0f, 16.0f / 16.0f),
		vec2(3.0f / 16.0f, 16.0f / 16.0f),

		// SAND
		vec2(4.0f / 16.0f, 15.0f / 16.0f),
		vec2(5.0f / 16.0f, 15.0f / 16.0f),
		vec2(5.0f / 16.0f, 16.0f / 16.0f),
		vec2(4.0f / 16.0f, 16.0f / 16.0f),

		// WATER
		vec2(5.0f / 16.0f, 15.0f / 16.0f),
		vec2(6.0f / 16.0f, 15.0f / 16.0f),
		vec2(6.0f / 16.0f, 16.0f / 16.0f),
		vec2(5.0f / 16.0f, 16.0f / 16.0f),

		// BEDROCK
		vec2(15.0f / 16.0f, 15.0f / 16.0f),
		vec2(16.0f / 16.0f, 15.0f / 16.0f),
		vec2(16.0f / 16.0f, 16.0f / 16.0f),
		vec2(15.0f / 16.0f, 16.0f / 16.0f),
	};

	static vec2 leftUv[] =
	{
		// GRASS
		vec2(1.0f / 16.0f, 15.0f / 16.0f),
		vec2(2.0f / 16.0f, 15.0f / 16.0f),
		vec2(2.0f / 16.0f, 16.0f / 16.0f),
		vec2(1.0f / 16.0f, 16.0f / 16.0f),

		// DIRT
		vec2(2.0f / 16.0f, 15.0f / 16.0f),
		vec2(3.0f / 16.0f, 15.0f / 16.0f),
		vec2(3.0f / 16.0f, 16.0f / 16.0f),
		vec2(2.0f / 16.0f, 16.0f / 16.0f),

		// STONE
		vec2(3.0f / 16.0f, 15.0f / 16.0f),
		vec2(4.0f / 16.0f, 15.0f / 16.0f),
		vec2(4.0f / 16.0f, 16.0f / 16.0f),
		vec2(3.0f / 16.0f, 16.0f / 16.0f),

		// SAND
		vec2(4.0f / 16.0f, 15.0f / 16.0f),
		vec2(5.0f / 16.0f, 15.0f / 16.0f),
		vec2(5.0f / 16.0f, 16.0f / 16.0f),
		vec2(4.0f / 16.0f, 16.0f / 16.0f),

		// WATER
		vec2(5.0f / 16.0f, 15.0f / 16.0f),
		vec2(6.0f / 16.0f, 15.0f / 16.0f),
		vec2(6.0f / 16.0f, 16.0f / 16.0f),
		vec2(5.0f / 16.0f, 16.0f / 16.0f),

		// BEDROCK
		vec2(15.0f / 16.0f, 15.0f / 16.0f),
		vec2(16.0f / 16.0f, 15.0f / 16.0f),
		vec2(16.0f / 16.0f, 16.0f / 16.0f),
		vec2(15.0f / 16.0f, 16.0f / 16.0f),
	};

	static vec2 frontUv[] =
	{
		// GRASS
		vec2(1.0f / 16.0f, 15.0f / 16.0f),
		vec2(2.0f / 16.0f, 15.0f / 16.0f),
		vec2(2.0f / 16.0f, 16.0f / 16.0f),
		vec2(1.0f / 16.0f, 16.0f / 16.0f),

		// DIRT
		vec2(2.0f / 16.0f, 15.0f / 16.0f),
		vec2(3.0f / 16.0f, 15.0f / 16.0f),
		vec2(3.0f / 16.0f, 16.0f / 16.0f),
		vec2(2.0f / 16.0f, 16.0f / 16.0f),

		// STONE
		vec2(3.0f / 16.0f, 15.0f / 16.0f),
		vec2(4.0f / 16.0f, 15.0f / 16.0f),
		vec2(4.0f / 16.0f, 16.0f / 16.0f),
		vec2(3.0f / 16.0f, 16.0f / 16.0f),

		// SAND
		vec2(4.0f / 16.0f, 15.0f / 16.0f),
		vec2(5.0f / 16.0f, 15.0f / 16.0f),
		vec2(5.0f / 16.0f, 16.0f / 16.0f),
		vec2(4.0f / 16.0f, 16.0f / 16.0f),

		// WATER
		vec2(5.0f / 16.0f, 15.0f / 16.0f),
		vec2(6.0f / 16.0f, 15.0f / 16.0f),
		vec2(6.0f / 16.0f, 16.0f / 16.0f),
		vec2(5.0f / 16.0f, 16.0f / 16.0f),

		// BEDROCK
		vec2(15.0f / 16.0f, 15.0f / 16.0f),
		vec2(16.0f / 16.0f, 15.0f / 16.0f),
		vec2(16.0f / 16.0f, 16.0f / 16.0f),
		vec2(15.0f / 16.0f, 16.0f / 16.0f),
	};

	static vec2 backUv[] =
	{
		// GRASS
		vec2(1.0f / 16.0f, 15.0f / 16.0f),
		vec2(2.0f / 16.0f, 15.0f / 16.0f),
		vec2(2.0f / 16.0f, 16.0f / 16.0f),
		vec2(1.0f / 16.0f, 16.0f / 16.0f),

		// DIRT
		vec2(2.0f / 16.0f, 15.0f / 16.0f),
		vec2(3.0f / 16.0f, 15.0f / 16.0f),
		vec2(3.0f / 16.0f, 16.0f / 16.0f),
		vec2(2.0f / 16.0f, 16.0f / 16.0f),

		// STONE
		vec2(3.0f / 16.0f, 15.0f / 16.0f),
		vec2(4.0f / 16.0f, 15.0f / 16.0f),
		vec2(4.0f / 16.0f, 16.0f / 16.0f),
		vec2(3.0f / 16.0f, 16.0f / 16.0f),

		// SAND
		vec2(4.0f / 16.0f, 15.0f / 16.0f),
		vec2(5.0f / 16.0f, 15.0f / 16.0f),
		vec2(5.0f / 16.0f, 16.0f / 16.0f),
		vec2(4.0f / 16.0f, 16.0f / 16.0f),

		// WATER
		vec2(5.0f / 16.0f, 15.0f / 16.0f),
		vec2(6.0f / 16.0f, 15.0f / 16.0f),
		vec2(6.0f / 16.0f, 16.0f / 16.0f),
		vec2(5.0f / 16.0f, 16.0f / 16.0f),

		// BEDROCK
		vec2(15.0f / 16.0f, 15.0f / 16.0f),
		vec2(16.0f / 16.0f, 15.0f / 16.0f),
		vec2(16.0f / 16.0f, 16.0f / 16.0f),
		vec2(15.0f / 16.0f, 16.0f / 16.0f),
	};
};