#include "Hud.h"
#include "Game.h"

Hud::Hud()
{
	m_projection = mat4(1.0f);
}

Hud::~Hud()
{
}

void Hud::create()
{
	float width = Game::GetInstance()->getWindow().getWidth();
	float height = Game::GetInstance()->getWindow().getHeight();

	m_projection = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
	Game::GetInstance()->getHudShader().setMat4("projection", m_projection);
}

void Hud::destroy()
{
}

void Hud::update()
{
}

void Hud::render()
{
}
