#pragma once

#include "Window.h"
#include "World.h"
#include "Hud.h"
#include "Shader.h"
#include "Timer.h"

class Game
{
private:
	Game();

public:
	static Game* GetInstance();
	~Game();

	void run();
	void exit();

	Window& getWindow() { return m_wnd; }
	Shader& getShader() { return m_shader; }
	Timer& getTimer() { return m_timer; }
	World& getWorld() { return m_world; }

private:
	void loop();
	void frame();

private:
	static Game* s_instance;

	Window m_wnd;
	Shader m_shader;
	Timer m_timer;
	World m_world;
	Hud m_hud;

	bool m_running;
};

