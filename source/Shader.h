#pragma once

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Shader
{
public:
	Shader();
	~Shader();

	void create(const char* vPath, const char* fPath);
	void destroy();
	void bind();
	void unbind();

	void setMat4(const char* name, const mat4& mat);
	void setInt(const char* name, int value);

private:
	void compileShader(unsigned int shader, const char* path, int shaderType);
	void checkCompileStatus(unsigned int shader, const char* type);

private:
	unsigned int m_id;
};

