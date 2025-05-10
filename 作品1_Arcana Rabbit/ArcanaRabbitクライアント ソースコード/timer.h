#pragma once
#include "Component.h"
#include "gameObject.h"

class Timer :public GameObject
{
private:
	float m_Time;
public:
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
};

