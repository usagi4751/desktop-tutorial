#pragma once
#include "scene.h"
#include "Component.h"
#include "draw2d_Manager.h"
class TextForm;
class Buttun;
class DummyMember;
class TestUDPScene :public Scene
{

	DummyMember* m_DummyMember[20];

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

};
