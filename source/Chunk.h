#pragma once

#include "Transform.h"
#include "Mesh.h"
#include "Block.h"

constexpr vec3 CHUNK_SIZE = ivec3(16, 256, 16);

class Chunk
{
public:
	Chunk();
	~Chunk();

	void start();
	void initialize();
	void destroy();
	void update();
	void render();

	Transform& getTransform() { return m_transform; }
	bool getStartState() { return m_wasStartExecuted; }
	BlockType getBlockTypeAt(ivec3 position);

	void setBlockTypeAt(ivec3 position, BlockType type);

	void regenerateMesh();

private:
	void generateMesh();
	void initializeBlocks();
	void iterateBlocks();
	void processBlock(int x, int y, int z);
	bool isFaceVisible(int x, int y, int z);
	void addFaceData(int x, int y, int z, int faceIndex);
	bool isBlockHiddenInChunk(int x, int y, int z);
	bool isBlockHiddenInWorld(vec3 globalPosition);
	BlockType determineBlockType(vec3 position);

private:
	Transform m_transform;
	Mesh m_mesh;

	Block*** m_blocks;

	bool m_wasStartExecuted;
	ivec3 m_chunkSize;
};

