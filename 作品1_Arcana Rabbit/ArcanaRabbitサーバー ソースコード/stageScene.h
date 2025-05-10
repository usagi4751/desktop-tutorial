#pragma once
#include "scene.h"
class Stage1Scene :public Scene
{
private:
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
};
