#include "Chunk.h"
#include "Game.h"
#include <iostream>

Chunk::Chunk()
{
	m_transform = Transform();
	m_mesh = Mesh();

	m_chunkSize = CHUNK_SIZE;

	m_blocks = new Block * *[(int)m_chunkSize.x];
	for (int x = 0; x < m_chunkSize.x; x++)
	{
		m_blocks[x] = new Block * [(int)m_chunkSize.y];
		for (int y = 0; y < m_chunkSize.y; y++)
		{
			m_blocks[x][y] = new Block[(int)m_chunkSize.z];
		}
	}

	m_wasStartExecuted = false;
}

Chunk::~Chunk()
{
}

void Chunk::start()
{
	generateMesh();

	m_wasStartExecuted = true;
}

void Chunk::initialize()
{
	initializeBlocks();
}

void Chunk::destroy()
{
	for(int x = 0; x < m_chunkSize.x; x++)
	{
		for (int y = 0; y < m_chunkSize.y; y++)
		{
			delete[] m_blocks[x][y];
		}
		delete[] m_blocks[x];
	}
	delete[] m_blocks;
}

void Chunk::update()
{
	m_transform.update();
}

void Chunk::render()
{
	auto& shader = Game::GetInstance()->getShader();
	shader.setMat4("model", m_transform.getModel());

	shader.bind();
	m_mesh.render();
	shader.unbind();
}

BlockType Chunk::getBlockTypeAt(ivec3 position)
{
	int x = position.x;
	int y = position.y;
	int z = position.z;

	if (x >= 0 && x < m_chunkSize.x && y >= 0 && y < m_chunkSize.y && z >= 0 && z < m_chunkSize.z)
		return m_blocks[x][y][z].m_type;

	return AIR;
}

void Chunk::setBlockTypeAt(ivec3 position, BlockType type)
{
	int x = position.x;
	int y = position.y;
	int z = position.z;

	if (x >= 0 && x < m_chunkSize.x && y >= 0 && y < m_chunkSize.y && z >= 0 && z < m_chunkSize.z)
		m_blocks[x][y][z].m_type = type;
}

void Chunk::generateMesh()
{
	iterateBlocks();

	m_mesh.generate();
}

void Chunk::regenerateMesh()
{
	m_mesh.clear();
	generateMesh();
}

void Chunk::initializeBlocks()
{
	for(int x = 0; x < m_chunkSize.x; x++)
	{
		for (int y = 0; y < m_chunkSize.y; y++)
		{
			for (int z = 0; z < m_chunkSize.z; z++)
			{
				m_blocks[x][y][z].m_position = m_transform.m_position + vec3(x, y, z);

				if(y < m_chunkSize.y / 2)
					m_blocks[x][y][z].m_type = BlockType::DIRT;
				else
					m_blocks[x][y][z].m_type = BlockType::AIR;
			}
		}
	}
}

void Chunk::iterateBlocks()
{
	for (int x = 0; x < m_chunkSize.x; x++)
	{
		for (int y = 0; y < m_chunkSize.y; y++)
		{
			for (int z = 0; z < m_chunkSize.z; z++)
			{
				processBlock(x, y, z);
			}
		}
	}
}

void Chunk::processBlock(int x, int y, int z)
{
	Block block = m_blocks[x][y][z];

	if (block.m_type == BlockType::AIR)
		return;

	bool facesVisible[6] = { false };

	facesVisible[0] = isFaceVisible(x, y + 1, z); // top
	facesVisible[1] = isFaceVisible(x, y - 1, z); // bottom
	facesVisible[2] = isFaceVisible(x - 1, y, z); // left
	facesVisible[3] = isFaceVisible(x + 1, y, z); // right
	facesVisible[4] = isFaceVisible(x, y, z + 1); // front
	facesVisible[5] = isFaceVisible(x, y, z - 1); // back

	for (int i = 0; i < 6; i++)
	{
		if (facesVisible[i])
		{
			addFaceData(x, y, z, i);
		}
	}
}

bool Chunk::isFaceVisible(int x, int y, int z)
{
	vec3 globalPosition = m_transform.m_position + vec3(x, y, z);

	return isBlockHiddenInChunk(x, y, z) && isBlockHiddenInWorld(globalPosition);
}

void Chunk::addFaceData(int x, int y, int z, int faceIndex)
{
	BlockType type = m_blocks[x][y][z].m_type;
	
	if (faceIndex == 0) // top
	{
		m_mesh.addVertex({ x	, y + 1, z, 0, 0, 0, BlockData::topUv[(type - 1) * 4 + 0].x,  BlockData::topUv[(type - 1) * 4 + 0].y });
		m_mesh.addVertex({ x	, y + 1, z + 1, 0, 0, 0, BlockData::topUv[(type - 1) * 4 + 1].x,  BlockData::topUv[(type - 1) * 4 + 1].y });
		m_mesh.addVertex({ x + 1, y + 1, z + 1, 0, 0, 0, BlockData::topUv[(type - 1) * 4 + 2].x,  BlockData::topUv[(type - 1) * 4 + 2].y });
		m_mesh.addVertex({ x + 1, y + 1, z, 0, 0, 0, BlockData::topUv[(type - 1) * 4 + 3].x,  BlockData::topUv[(type - 1) * 4 + 3].y });
	}
	else if (faceIndex == 1) // bottom
	{
		m_mesh.addVertex({ x	, y, z, 0, 0, 0, BlockData::bottomUv[(type - 1) * 4 + 0].x,  BlockData::bottomUv[(type - 1) * 4 + 0].y });
		m_mesh.addVertex({ x + 1, y, z, 0, 0, 0, BlockData::bottomUv[(type - 1) * 4 + 1].x,  BlockData::bottomUv[(type - 1) * 4 + 1].y });
		m_mesh.addVertex({ x + 1, y, z + 1, 0, 0, 0, BlockData::bottomUv[(type - 1) * 4 + 2].x,  BlockData::bottomUv[(type - 1) * 4 + 2].y });
		m_mesh.addVertex({ x	, y, z + 1, 0, 0, 0, BlockData::bottomUv[(type - 1) * 4 + 3].x,  BlockData::bottomUv[(type - 1) * 4 + 3].y });
	}
	else if (faceIndex == 2) // left
	{
		m_mesh.addVertex({ x, y, z, 0, 0, 0, BlockData::leftUv[(type - 1) * 4 + 0].x,  BlockData::leftUv[(type - 1) * 4 + 0].y });
		m_mesh.addVertex({ x, y, z + 1, 0, 0, 0, BlockData::leftUv[(type - 1) * 4 + 1].x,  BlockData::leftUv[(type - 1) * 4 + 1].y });
		m_mesh.addVertex({ x, y + 1, z + 1, 0, 0, 0, BlockData::leftUv[(type - 1) * 4 + 2].x,  BlockData::leftUv[(type - 1) * 4 + 2].y });
		m_mesh.addVertex({ x, y + 1, z, 0, 0, 0, BlockData::leftUv[(type - 1) * 4 + 3].x,  BlockData::leftUv[(type - 1) * 4 + 3].y });
	}
	else if (faceIndex == 3) // right
	{
		m_mesh.addVertex({ x + 1, y, z + 1, 0, 0, 0, BlockData::rightUv[(type - 1) * 4 + 0].x,  BlockData::rightUv[(type - 1) * 4 + 0].y });
		m_mesh.addVertex({ x + 1, y, z, 0, 0, 0, BlockData::rightUv[(type - 1) * 4 + 1].x,  BlockData::rightUv[(type - 1) * 4 + 1].y });
		m_mesh.addVertex({ x + 1, y + 1, z, 0, 0, 0, BlockData::rightUv[(type - 1) * 4 + 2].x,  BlockData::rightUv[(type - 1) * 4 + 2].y });
		m_mesh.addVertex({ x + 1, y + 1, z + 1, 0, 0, 0, BlockData::rightUv[(type - 1) * 4 + 3].x,  BlockData::rightUv[(type - 1) * 4 + 3].y });
	}
	else if (faceIndex == 4) // front
	{
		m_mesh.addVertex({ x, y, z + 1, 0, 0, 0, BlockData::frontUv[(type - 1) * 4 + 0].x,  BlockData::frontUv[(type - 1) * 4 + 0].y });
		m_mesh.addVertex({ x + 1, y, z + 1, 0, 0, 0, BlockData::frontUv[(type - 1) * 4 + 1].x,  BlockData::frontUv[(type - 1) * 4 + 1].y });
		m_mesh.addVertex({ x + 1, y + 1, z + 1, 0, 0, 0, BlockData::frontUv[(type - 1) * 4 + 2].x,  BlockData::frontUv[(type - 1) * 4 + 2].y });
		m_mesh.addVertex({ x, y + 1, z + 1, 0, 0, 0, BlockData::frontUv[(type - 1) * 4 + 3].x,  BlockData::frontUv[(type - 1) * 4 + 3].y });
	}
	else if (faceIndex == 5) // back
	{
		m_mesh.addVertex({ x + 1, y, z, 0, 0, 0, BlockData::backUv[(type - 1) * 4 + 0].x,  BlockData::backUv[(type - 1) * 4 + 0].y });
		m_mesh.addVertex({ x, y, z, 0, 0, 0, BlockData::backUv[(type - 1) * 4 + 1].x,  BlockData::backUv[(type - 1) * 4 + 1].y });
		m_mesh.addVertex({ x, y + 1, z, 0, 0, 0, BlockData::backUv[(type - 1) * 4 + 2].x,  BlockData::backUv[(type - 1) * 4 + 2].y });
		m_mesh.addVertex({ x + 1, y + 1, z, 0, 0, 0, BlockData::backUv[(type - 1) * 4 + 3].x,  BlockData::backUv[(type - 1) * 4 + 3].y });
	}
	
	m_mesh.addIndex(m_mesh.getVertexCount() - 4);
	m_mesh.addIndex(m_mesh.getVertexCount() - 3);
	m_mesh.addIndex(m_mesh.getVertexCount() - 2);

	m_mesh.addIndex(m_mesh.getVertexCount() - 4);
	m_mesh.addIndex(m_mesh.getVertexCount() - 2);
	m_mesh.addIndex(m_mesh.getVertexCount() - 1);
}

bool Chunk::isBlockHiddenInChunk(int x, int y, int z)
{
	if (x < 0 || x >= m_chunkSize.x || y < 0 || y >= m_chunkSize.y || z < 0 || z >= m_chunkSize.z)
		return true;
	return m_blocks[x][y][z].m_type == BlockType::AIR;
}

bool Chunk::isBlockHiddenInWorld(vec3 globalPosition)
{
	Chunk* neighborChunk = Game::GetInstance()->getWorld().getChunkAt(globalPosition);
	if(neighborChunk == nullptr)
		return true;

	vec3 localPosition = neighborChunk->getTransform().inverseTransformPoint(globalPosition);

	BlockType type = neighborChunk->getBlockTypeAt(localPosition);

	return type == BlockType::AIR;
}
