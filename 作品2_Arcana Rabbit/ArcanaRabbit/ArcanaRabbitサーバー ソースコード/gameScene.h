#pragma once
#include "scene.h"
class gameScene:public Scene
{
	GameObject* testdraw;//�e�X�g�p
	float fade = 1.0f;
	float fadeout = 0.0f;
private:
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void fadein() override {fadeout += 0.01f;};
};
