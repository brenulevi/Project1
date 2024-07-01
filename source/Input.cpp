#include "Input.h"

bool Input::m_keys[256] = { false };
bool Input::m_mouseKeys[3] = { false };
int Input::m_mouseX = 0;
int Input::m_mouseY = 0;
int Input::m_mouseDeltaX = 0;
int Input::m_mouseDeltaY = 0;

bool Input::isKeyPressed(int key)
{
    auto result = m_keys[key];
	m_keys[key] = false;
	return result;
}

bool Input::isKeyReleased(int key)
{
	return !m_keys[key];
}

bool Input::isKeyHeld(int key)
{
	return m_keys[key];
}

bool Input::isMouseKeyPressed(int key)
{
	auto result = m_mouseKeys[key];
	m_mouseKeys[key] = false;
	return result;
}

bool Input::isMouseKeyReleased(int key)
{
	return !m_mouseKeys[key];
}

bool Input::isMouseKeyHeld(int key)
{
	return m_mouseKeys[key];
}

int Input::getMouseX()
{
	return m_mouseX;
}

int Input::getMouseY()
{
	return m_mouseY;
}

int Input::getMouseDeltaX()
{
	int result = m_mouseDeltaX;
	m_mouseDeltaX = 0;
	return result;
}

int Input::getMouseDeltaY()
{
	int result = m_mouseDeltaY;
	m_mouseDeltaY = 0;
	return result;
}

void Input::setKeyPressed(int key)
{
	m_keys[key] = true;
}

void Input::setKeyReleased(int key)
{
	m_keys[key] = false;
}

void Input::setMouseKeyPressed(int key)
{
	m_mouseKeys[key] = true;
}

void Input::setMouseReleased(int key)
{
	m_mouseKeys[key] = false;
}

void Input::setMousePosition(int x, int y)
{
	m_mouseX = x;
	m_mouseY = y;
}

void Input::setMouseDelta(int x, int y)
{
	m_mouseDeltaX = x;
	m_mouseDeltaY = y;
}
