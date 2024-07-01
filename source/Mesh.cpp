#include "Mesh.h"
#include <glad/glad.h>

Mesh::Mesh()
{
	m_vao = 0;
	m_vbo = 0;
	m_ebo = 0;
}

Mesh::~Mesh()
{
}

void Mesh::destroy()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);

	m_vertices.clear();
	m_indices.clear();

	m_vao = 0;
	m_vbo = 0;
	m_ebo = 0;
}

void Mesh::render()
{
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, (unsigned int)m_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::addVertex(Vertex vertex)
{
	m_vertices.push_back(vertex);
}

void Mesh::addIndex(unsigned int index)
{
	m_indices.push_back(index);
}

void Mesh::generate()
{
	glGenVertexArrays(1, &m_vao);

	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::clear()
{
	m_vertices.clear();
	m_indices.clear();

	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);

	m_vao = 0;
	m_vbo = 0;
	m_ebo = 0;
}
