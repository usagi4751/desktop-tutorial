#pragma once


#pragma once
#include "Component.h"
#include "gameObject.h"

class explosion :public GameObject
{
private:
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;

	int m_ct;
	int m_count{};

	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture = nullptr;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;


public:
	virtual void Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
};

