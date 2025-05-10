#pragma once
#include "main.h"
//==========================
// �v���C���[�̖��O�𓪂̏�ɏo���ׂ̃N���X
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

