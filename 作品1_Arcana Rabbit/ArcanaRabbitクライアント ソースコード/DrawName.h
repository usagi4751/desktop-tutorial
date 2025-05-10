#pragma once
#include "main.h"
//==========================
// プレイヤーの名前を頭の上に出す為のクラス
//==========================
class DrawName
{
private:

	ID3D11Buffer* m_VertexBuffer = nullptr;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

public:
	void Init();
	void UnInit();
	void Draw(XMFLOAT3 pos);
	void SetName(std::string name);
};

