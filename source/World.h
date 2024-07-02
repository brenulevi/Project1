#pragma once

#include "Player.h"
#include "Chunk.h"
#include "Texture.h"
#include <unordered_map>

struct KeyFuncs
{
	size_t operator()(const vec3& k) const
	{
		return std::hash<float>()(k.x) ^ std::hash<float>()(k.y) ^ std::hash<float>()(k.z);
	}

	bool operator()(const vec3& a, const vec3& b) const
	{
		return a.x == b.x && a.y == b.y && a.z == b.z;
	}
};

constexpr int WORLD_SIZE = 24;

class World
{
public:
	World();
	~World();

	void create();
	void destroy();
	void update();
	void render();

	Chunk* getChunkAt(vec3 position);

private:
	void generateWorld();
	void setPlayerPositionOnCenter();

private:
	Player m_player;
	std::unordered_map<vec3, Chunk*, KeyFuncs, KeyFuncs> m_chunks;

	int m_frameCount;
	float m_totalTime;
	int m_worldSize;
	ivec3 m_chunkSize;

	Texture m_atlas;
};

