#pragma once
#include "scene.h"
#include "Component.h"
#include "draw2d_Manager.h"
class TextForm;
class Buttun;
class Camera;
class titleScene :public Scene
{
	UI_Tex m_fade;

	UI_Text m_PortFormText;
	UI_Text m_NameFormText;
	UI_Text m_PasswordFormText;

	TextForm* m_IpAddressForm;
	TextForm* m_NameForm;
	TextForm* m_PasswordForm;

	Buttun* m_StartButtun;


	Component* m_audio;
	float fade = 0;
	float tennmetu  = 0;
	XMFLOAT2		BezierPoint[120];
	Camera* m_camera;
	float m_bezitime = 0.01;
	float m_townnomaltime = 0.00f;
	float m_stagetime = 0.00f;
	float m_effectfade = 0.00f;
	virtual void Init() override;
	virtual void Uninit() override;
	virtual void Update() override;
	virtual void Draw() override;
};
