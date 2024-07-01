#include "Timer.h"

Timer::Timer()
{
	m_deltaTime = 0.0f;
}

Timer::~Timer()
{
}

void Timer::initialize()
{
	QueryPerformanceFrequency(&m_frequency);
	QueryPerformanceCounter(&m_start);
	m_current = m_start;
}

void Timer::update()
{
	QueryPerformanceCounter(&m_stop);

	m_deltaTime = (float)(m_stop.QuadPart - m_current.QuadPart) / (float)m_frequency.QuadPart;

	m_current = m_stop;
}

float Timer::peek()
{
	QueryPerformanceCounter(&m_stop);

	m_deltaTime = (float)(m_stop.QuadPart - m_start.QuadPart) / (float)m_frequency.QuadPart;

	return m_deltaTime;
}

float Timer::getDeltaTime()
{
	return m_deltaTime;
}
