#include "Window.h"
#include "glad/glad.h"
#include "fstream"
#include "Input.h"
#include "resource.h"
#include <gl/GL.h>

Window::Window()
{
	m_hwnd = NULL;
	m_hdc = NULL;
	m_width = WINDOW_WIDTH;
	m_height = WINDOW_HEIGHT;
	m_title = WINDOW_TITLE;
	m_fullscreen = FULLSCREEN;
	m_vsync = VSYNC;
	m_polygonMode = SOLID;
}

Window::~Window()
{
}

void Window::create()
{
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(WNDCLASS));

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = Window::sWndProc;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hIcon = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "Game";

	RegisterClass(&wc);

	if (m_fullscreen)
	{
		m_width = GetSystemMetrics(SM_CXSCREEN);
		m_height = GetSystemMetrics(SM_CYSCREEN);

		m_hwnd = CreateWindow(
			wc.lpszClassName,
			m_title,
			WS_POPUP,
			0,
			0,
			m_width,
			m_height,
			NULL,
			NULL,
			wc.hInstance,
			this
		);
	}
	else
	{
		RECT winRect = { 0, 0, m_width, m_height };
		AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);

		int w = winRect.right - winRect.left;
		int h = winRect.bottom - winRect.top;

		int posX = GetSystemMetrics(SM_CXSCREEN) / 2 - w / 2;
		int posY = GetSystemMetrics(SM_CYSCREEN) / 2 - h / 2;

		m_hwnd = CreateWindow(
			wc.lpszClassName,
			m_title,
			WS_OVERLAPPEDWINDOW,
			posX,
			posY,
			w,
			h,
			NULL,
			NULL,
			wc.hInstance,
			this
		);
	}

	ShowWindow(m_hwnd, SW_SHOW);
	SetFocus(m_hwnd);
	UpdateWindow(m_hwnd);

	createGLContext();
	getGLInfo();
	setupGL();

	setupInputs();
}

void Window::destroy()
{
	DestroyWindow(m_hwnd);
	UnregisterClass("Game", GetModuleHandle(NULL));

	m_hwnd = NULL;

	wglMakeCurrent(m_hdc, NULL);
	ReleaseDC(m_hwnd, m_hdc);
	m_hdc = NULL;
}

void Window::treatMessages(bool* gameRunState)
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		if(msg.message == WM_QUIT)
		{
			*gameRunState = false;
		}
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swapBuffers()
{
	SwapBuffers(GetDC(m_hwnd));
}

void Window::setViewport()
{
	RECT rect;
	GetClientRect(m_hwnd, &rect);
	glViewport(0, 0, rect.right, rect.bottom);
}

void Window::setTitle(const char* title)
{
	m_title = title;
	SetWindowText(m_hwnd, title);
}

void Window::setPolygonMode(PolygonMode mode)
{
	m_polygonMode = mode;
	glPolygonMode(GL_FRONT_AND_BACK, mode);
}

LRESULT Window::sWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* wnd;

	if(msg == WM_NCCREATE)
	{
		CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		wnd = reinterpret_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(wnd));

		wnd->m_hwnd = hwnd;
	}
	else
	{
		wnd = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	}

	if(wnd)
	{
		return wnd->wndProc(hwnd, msg, wParam, lParam);
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

LRESULT Window::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;

	case WM_SIZE:
		if (m_hdc == NULL)
			break;
		m_width = LOWORD(lParam);
		m_height = HIWORD(lParam);
		setViewport();
		break;
	case WM_KEYDOWN:
		Input::setKeyPressed((int)wParam);
		break;
	case WM_KEYUP:
		Input::setKeyReleased((int)wParam);
		break;
	case WM_MOUSEMOVE:
		Input::setMousePosition(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_LBUTTONDOWN:
		Input::setMouseKeyPressed(VK_LBUTTON);
		break;
	case WM_LBUTTONUP:
		Input::setMouseReleased(VK_LBUTTON);
		break;
	case WM_RBUTTONDOWN:
		Input::setMouseKeyPressed(VK_RBUTTON);
		break;
	case WM_RBUTTONUP:
		Input::setMouseReleased(VK_RBUTTON);
		break;
	case WM_MBUTTONDOWN:
		Input::setMouseKeyPressed(VK_MBUTTON);
		break;
	case WM_MBUTTONUP:
		Input::setMouseReleased(VK_MBUTTON);
		break;
	case WM_SETFOCUS:
	{

		RECT clientRect;
		ZeroMemory(&clientRect, sizeof(RECT));
		GetClientRect(hwnd, &clientRect);

		POINT topLeft = { clientRect.left, clientRect.top };
		POINT bottomRight = { clientRect.right, clientRect.bottom };

		ClientToScreen(hwnd, &topLeft);
		ClientToScreen(hwnd, &bottomRight);

		RECT screenRect;
		ZeroMemory(&screenRect, sizeof(RECT));
		screenRect.left = topLeft.x + 1;
		screenRect.top = topLeft.y + 1;
		screenRect.right = bottomRight.x - 1;
		screenRect.bottom = bottomRight.y - 1;

		ClipCursor(&screenRect);
		ShowCursor(false);
		break;
	}
	case WM_KILLFOCUS:
		ClipCursor(NULL);
		ShowCursor(true);
		break;
	case WM_INPUT:
	{
		UINT dwSize;
		ZeroMemory(&dwSize, sizeof(UINT));

		GetRawInputData((HRAWINPUT)lParam,
			RID_INPUT,
			NULL,
			&dwSize,
			sizeof(RAWINPUTHEADER)
		);

		LPBYTE lpb = new BYTE[dwSize];
		if (lpb == NULL)
		{
			break;
		}

		GetRawInputData((HRAWINPUT)lParam,
			RID_INPUT,
			lpb,
			&dwSize,
			sizeof(RAWINPUTHEADER)
		);

		RAWINPUT* raw = (RAWINPUT*)lpb;

		if (raw->header.dwType == RIM_TYPEMOUSE)
		{
			Input::setMouseDelta(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
		}

		delete[] lpb;

		break;
	}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Window::createGLContext()
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;

	m_hdc = GetDC(m_hwnd);
	int nPixelFormat = ChoosePixelFormat(m_hdc, &pfd);
	SetPixelFormat(m_hdc, nPixelFormat, &pfd);
	HGLRC tempContext = wglCreateContext(m_hdc);
	wglMakeCurrent(m_hdc, tempContext);

	gladLoadGL();

	typedef BOOL (WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int interval);
	PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = nullptr;
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	wglSwapIntervalEXT(m_vsync);
}

void Window::getGLInfo()
{
	std::ofstream file("glinfo.txt");

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* shadingLanguageVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

	file << "Renderer: " << renderer << std::endl;
	file << "Version: " << version << std::endl;
	file << "Vendor: " << vendor << std::endl;
	file << "Shading Language Version: " << shadingLanguageVersion << std::endl;
}

void Window::setupGL()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Window::setupInputs()
{
	RAWINPUTDEVICE rid[1];
	rid[0].usUsagePage = 0x01;
	rid[0].usUsage = 0x02;
	rid[0].dwFlags = RIDEV_INPUTSINK;
	rid[0].hwndTarget = m_hwnd;

	RegisterRawInputDevices(rid, 1, sizeof(rid[0]));
}
