#pragma once
//==========================================
//プレイヤーを表示するだけのクラス
//==========================================
#include "Component.h"
#include "gameObject.h"
class DrawName;
class Member :public GameObject
{
private:

	DrawName* m_DrawName;
	Component* m_Component{};
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	XMFLOAT4 m_quat = { 0.0f,0.0f ,0.0f ,1.0f };
	bool m_Active;

public:
	Member() { m_Component = nullptr; }
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	void SetActive(bool active);
	void SetName(std::string name);
};

