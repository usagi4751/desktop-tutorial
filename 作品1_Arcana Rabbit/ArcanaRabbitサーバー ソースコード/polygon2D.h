#pragma once
#include "Component.h"
#include "gameObject.h"
class Polygon2D :public GameObject {
private:
	ID3D11Buffer*				m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView*	m_Texture = nullptr;

	ID3D11VertexShader*			m_VertexShader;
	ID3D11PixelShader*			m_PixelShader;
	ID3D11InputLayout*			m_VertexLayout;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void Drawdrafault();
	void Drawmap();


};