#pragma once

#include <vector>

struct Vertex
{
	struct Position
	{
		float x;
		float y;
		float z;
	} position;

	struct Normal
	{
		float x;
		float y;
		float z;
	} normal;

	struct TexCoord
	{
		float u;
		float v;
	} texCoord;

	Vertex(int x, int y, int z, int nx, int ny, int nz, int u, int v)
	{
		position.x = (float)x;
		position.y = (float)y;
		position.z = (float)z;
		normal.x = (float)nx;
		normal.y = (float)ny;
		normal.z = (float)nz;
		texCoord.u = (float)u;
		texCoord.v = (float)v;
	}
	Vertex(int x, int y, int z, int nx, int ny, int nz, float u, float v)
	{
		position.x = (float)x;
		position.y = (float)y;
		position.z = (float)z;
		normal.x = (float)nx;
		normal.y = (float)ny;
		normal.z = (float)nz;
		texCoord.u = u;
		texCoord.v = v;
	}
	Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v)
	{
		position.x = x;
		position.y = y;
		position.z = z;
		normal.x = nx;
		normal.y = ny;
		normal.z = nz;
		texCoord.u = u;
		texCoord.v = v;
	}
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void destroy();
	void render();

	void addVertex(Vertex vertex);
	void addIndex(unsigned int index);

	unsigned int getVertexCount() const { return (unsigned int)m_vertices.size(); }

	void generate();
	void clear();

private:
	unsigned int m_vao;
	unsigned int m_vbo;
	unsigned int m_ebo;

	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
};

