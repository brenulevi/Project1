#include "Texture.h"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture()
{
	m_id = 0;
	m_channels = 0;
	m_width = 0;
	m_height = 0;
	m_path = "";
}

Texture::~Texture()
{
}

void Texture::load(const char* path)
{
	m_path = path;

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path, &m_width, &m_height, &m_channels, 0);

	if (data)
	{
		GLenum format = 0;
		if (m_channels == 1)
			format = GL_RED;
		else if (m_channels == 3)
			format = GL_RGB;
		else if (m_channels == 4)
			format = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
