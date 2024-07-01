#pragma once

class Texture
{
public:
	Texture();
	~Texture();

	void load(const char* path);
	void bind();
	void unbind();

private:
	unsigned int m_id;
	int m_width;
	int m_height;
	int m_channels;
	const char* m_path;
};

