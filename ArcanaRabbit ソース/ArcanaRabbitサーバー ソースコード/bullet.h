#pragma once
#include "Component.h"
#include "gameObject.h"

class bullet :public GameObject
{
private:
	int m_life =120;
	Component* m_Component{};

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;


public:
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
};

