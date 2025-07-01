#pragma once
#include "renderer.h"
#include "gameObject.h"

#define MESHSIZE (256)
class meshField  : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11Buffer* m_IndexBuffer{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	VERTEX_3D m_Vertex[MESHSIZE][MESHSIZE];
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	float Getheight(XMFLOAT3 pos);

};

