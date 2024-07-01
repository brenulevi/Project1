#include "Shader.h"
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

Shader::Shader()
{
	m_id = 0;
}

Shader::~Shader()
{
}

void Shader::create(const char* vPath, const char* fPath)
{
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	compileShader(vertexShader, vPath, GL_VERTEX_SHADER);
	compileShader(fragmentShader, fPath, GL_FRAGMENT_SHADER);

	m_id = glCreateProgram();
	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);
	glLinkProgram(m_id);

	checkCompileStatus(m_id, "PROGRAM");
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::destroy()
{
	glDeleteProgram(m_id);
	m_id = 0;
}

void Shader::bind()
{
	glUseProgram(m_id);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::setMat4(const char* name, const mat4& mat)
{
	bind();
	unsigned int loc = glGetUniformLocation(m_id, name);
	glUniformMatrix4fv(loc, 1, GL_FALSE, &mat[0][0]);
	unbind();
}

void Shader::setInt(const char* name, int value)
{
	bind();
	unsigned int loc = glGetUniformLocation(m_id, name);
	glUniform1i(loc, value);
	unbind();
}

void Shader::compileShader(unsigned int shader, const char* path, int shaderType)
{
	std::ifstream file(path);

	if(!file.is_open())
	{
		return;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string source = buffer.str();
	const char* src = source.c_str();

	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	if(shaderType == GL_VERTEX_SHADER)
		checkCompileStatus(shader, "VERTEX");
	else
		checkCompileStatus(shader, "FRAGMENT");
}

void Shader::checkCompileStatus(unsigned int shader, const char* type)
{
	int success;
	char infoLog[512];

	if(type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

		if(!success)
		{
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::" << type << 
				"::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);

		if(!success)
		{
			glGetProgramInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::" << type << 
				"::LINK_FAILED\n" << infoLog << std::endl;
		}
	}
	
}
