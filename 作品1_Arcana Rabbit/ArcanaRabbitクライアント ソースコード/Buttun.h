#pragma once
#include "draw2d_Manager.h"
class UI_Text;
class UI_Tex;
//==================
//ボタン機能
//==================
class Buttun
{
private:
	XMFLOAT2 m_Pos = { 50.0f,50.0f};
	XMFLOAT2 m_Scale = { 100.0f,100.0f };
	UI_Tex m_ButtunTexture;
	bool m_Active = false;//表示するか

public:
	Buttun();
	void Uninit();
	//表示深度
	void SetDepth(float depth);
	//色　{R,G,B,A}
	void SetColer(XMFLOAT4 coler);
	//座標
	void SetPosition(XMFLOAT2 position);
	//大きさ
	void SetScale(XMFLOAT2 scale);
	//UV値
	void SetUV(XMFLOAT2   uv, XMFLOAT2   UV);
	//表示するか
	void SetActive(bool active);
	//テクスチャの設定　番号で決まる
	void SetTextuer(int textuer);
	bool OnMouseButtun();//マウスポインタがボタンに被っているか

};

