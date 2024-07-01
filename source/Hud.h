#pragma once

#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Hud
{
public:
	Hud();
	~Hud();

	void create();
	void destroy();
	void update();
	void render();

private:
	mat4 m_projection;
};

