#pragma once
#include "draw2d_Manager.h"
class UI_Text;
class UI_Tex;
class Buttun
{
private:
	XMFLOAT2 m_Pos = { 50.0f,50.0f};
	XMFLOAT2 m_Scale = { 100.0f,100.0f };
	UI_Tex m_ButtunTexture;
	bool m_Active = false;//表示するか

public:
	Buttun();
	void SetDepth(float depth);
	void SetColer(XMFLOAT4 coler);
	void SetPosition(XMFLOAT2 position);
	void SetScale(XMFLOAT2 scale);
	void SetUV(XMFLOAT2   uv, XMFLOAT2   UV);
	void SetActive(bool active);
	bool OnMouseButtun();//マウスポインタがボタンに被っているか

};

