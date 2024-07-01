#pragma once

#include <windows.h>

class Timer
{
public:
	Timer();
	~Timer();

	void initialize();
	void update();

	float peek();

	float getDeltaTime();

private:
	LARGE_INTEGER m_start;
	LARGE_INTEGER m_current;
	LARGE_INTEGER m_stop;
	LARGE_INTEGER m_frequency;

	float m_deltaTime;
};

