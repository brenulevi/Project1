#pragma once

class Input
{
public:
	static bool isKeyPressed(int key);
	static bool isKeyReleased(int key);
	static bool isKeyHeld(int key);
	static bool isMouseKeyPressed(int key);
	static bool isMouseKeyReleased(int key);
	static bool isMouseKeyHeld(int key);

	static int getMouseX();
	static int getMouseY();
	static int getMouseDeltaX();
	static int getMouseDeltaY();

	static void setKeyPressed(int key);
	static void setKeyReleased(int key);
	static void setMouseKeyPressed(int key);
	static void setMouseReleased(int key);
	static void setMousePosition(int x, int y);
	static void setMouseDelta(int x, int y);

private:
	static bool m_keys[256];
	static bool m_mouseKeys[3];
	static int m_mouseX;
	static int m_mouseY;
	static int m_mouseDeltaX;
	static int m_mouseDeltaY;
};

// Virtual Key Codes
#define VK_W 0x57
#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44
#define VK_ESCAPE 0x1B
#define VK_SPACE 0x20
#define VK_SHIFT 0x10
#define VK_P 0x50
#define VK_LBUTTON 0x01
#define VK_RBUTTON 0x02
#define VK_MBUTTON 0x04

