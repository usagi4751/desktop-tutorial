#include "timer.h"
void Timer::Init()
{
}

void Timer::Uninit()
{
}

void Timer::Update()
{
	m_Time += 1.0f / 60.0f;
}

void Timer::Draw()
{
	//Draw2d::SetText("Time" + std::to_string((int)m_Time), { 1600,0,1920,1080 }, 30, { 1.0f,1.0f,1.0f,1.0f }, 0.5f);
}
