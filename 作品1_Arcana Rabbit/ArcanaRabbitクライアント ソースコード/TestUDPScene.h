#pragma once
#include "scene.h"
#include "Component.h"
#include "UDP.h"
#include "draw2d_Manager.h"
class TextForm;
class Buttun;
class DrawName;
class TestUDPScene :public Scene
{
	//ƒeƒXƒg
	//std::string m_a;

	UI_Text m_Chat;

	UI_Text m_IpAddressFormText;
	UI_Text m_PortFormText;
	UI_Text m_NameFormText;

	TextForm* m_IpAddressForm;
	TextForm* m_PortForm;
	TextForm* m_NameForm;

	Buttun* m_StartButtun;
	Buttun* m_SendPlayerDataButtun;

	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;

};
