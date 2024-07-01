#include "Game.h"

Game* Game::s_instance = nullptr;

Game::Game()
{
	m_wnd = Window();
	m_hudShader = Shader();
	m_shader = Shader();
	m_timer = Timer();
	m_world = World();
	m_hud = Hud();

	m_running = false;
}

Game* Game::GetInstance()
{
	if(!s_instance)
	{
		s_instance = new Game();
		return s_instance;
	}

	return s_instance;
}

Game::~Game()
{
}

void Game::run()
{
	m_wnd.create();
	m_hudShader.create("resources/shaders/hud_vertex.shader", "resources/shaders/hud_fragment.shader");
	m_shader.create("resources/shaders/vertex.shader", "resources/shaders/fragment.shader");
	m_timer.initialize();
	m_world.create();
	m_hud.create();

	m_running = true;

	loop();

	m_world.destroy();
	m_hud.destroy();
	m_shader.destroy();
	m_hudShader.destroy();
	m_wnd.destroy();

	delete s_instance;
}

void Game::exit()
{
	m_running = false;
}

void Game::loop()
{
	while(m_running)
	{
		m_wnd.treatMessages(&m_running);

		frame();
	}
}

void Game::frame()
{
	m_timer.update();
	m_world.update();
	m_hud.update();

	m_wnd.clear();
	m_world.render();
	m_hud.render();
	m_wnd.swapBuffers();
}
