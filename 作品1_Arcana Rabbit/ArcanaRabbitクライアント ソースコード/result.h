#pragma once
#include "scene.h"
class resultScene :public Scene
{
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
};	
