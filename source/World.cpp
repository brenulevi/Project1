#include "World.h"
#include "Input.h"
#include "Game.h"
#include <string>
#include <iostream>

World::World()
{
	m_player = Player();
	m_atlas = Texture();

	m_frameCount = 0;
	m_totalTime = 0.0f;
	m_worldSize = WORLD_SIZE;
	m_chunkSize = CHUNK_SIZE;
}

World::~World()
{
}

void World::create()
{
	m_player.initialize();

	m_atlas.load("resources/textures/atlas.png");

	glActiveTexture(GL_TEXTURE0);
	m_atlas.bind();
	Game::GetInstance()->getShader().setInt("atlasTexture", 0);

	generateWorld();

	setPlayerPositionOnCenter();
}

void World::destroy()
{
	for(auto& chunk : m_chunks)
	{
		chunk.second->destroy();
		delete chunk.second;
	}
	m_chunks.clear();
}

void World::update()
{
	if (Input::isKeyPressed(VK_ESCAPE))
		Game::GetInstance()->exit();

	m_totalTime += Game::GetInstance()->getTimer().getDeltaTime();
	if (m_totalTime >= 1.0f)
	{
		std::string title = WINDOW_TITLE + std::string(" | FPS: ") + std::to_string(m_frameCount);
		Game::GetInstance()->getWindow().setTitle(title.c_str());
		m_frameCount = 0;
		m_totalTime -= 1.0f;
	}
	m_frameCount++;

	m_player.update();

	for(auto& chunk : m_chunks)
	{
		if(chunk.second->getStartState() == false)
			chunk.second->start();
		else
			chunk.second->update();
	}
}

void World::render()
{
	for(auto& chunk : m_chunks)
	{
		chunk.second->render();
	}
}

Chunk* World::getChunkAt(vec3 position)
{
	ivec3 chunkCoords = ivec3(
		floor(position.x / m_chunkSize.x) * m_chunkSize.x,
		floor(position.y / m_chunkSize.y) * m_chunkSize.y,
		floor(position.z / m_chunkSize.z) * m_chunkSize.z
	);

	auto it = m_chunks.find(vec3(chunkCoords));
	
	if(it != m_chunks.end())
		return it->second;

	return nullptr;
}

void World::generateWorld()
{
	for(int x = -m_worldSize; x < m_worldSize; x++)
	{
		for (int z = -m_worldSize; z < m_worldSize; z++)
		{
			vec3 chunkPosition = vec3(x * m_chunkSize.x, 0.0f, z * m_chunkSize.z);
			Chunk* chunk = new Chunk();
			chunk->getTransform().m_position = chunkPosition;
			chunk->initialize();
			m_chunks.insert({ chunkPosition, chunk });
		}
	}
}

void World::setPlayerPositionOnCenter()
{
	m_player.getTransform().m_position = vec3(0, m_chunkSize.y + 2, 0);
}
