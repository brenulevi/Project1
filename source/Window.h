#pragma once

#include <windows.h>
#include <windowsx.h>
#include <glad/glad.h>

constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;
constexpr const char* WINDOW_TITLE = "Game";
constexpr bool FULLSCREEN = false;
constexpr bool VSYNC = false;

enum PolygonMode
{
	WIREFRAME = GL_LINE,
	SOLID
};

class Window
{
public:
	Window();
	~Window();

	void create();
	void destroy();

	void treatMessages(bool* gameRunState);

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	PolygonMode getPolygonMode() const { return m_polygonMode; }

	void clear();
	void swapBuffers();

	void setViewport();
	void setTitle(const char* title);
	void setPolygonMode(PolygonMode mode);

private:
	static LRESULT CALLBACK sWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	void createGLContext();
	void getGLInfo();
	void setupGL();
	void setupInputs();

private:
	HWND m_hwnd;
	HDC m_hdc;
	int m_width;
	int m_height;
	const char* m_title;
	bool m_fullscreen;
	bool m_vsync;
	PolygonMode m_polygonMode;
};