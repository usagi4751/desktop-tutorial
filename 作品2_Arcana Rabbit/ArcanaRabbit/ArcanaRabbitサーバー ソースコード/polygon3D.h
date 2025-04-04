#pragma once
#include "gameObject.h"
class Floor;
class Player;
class Field : public GameObject
{
private:
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;

	ID3D11Buffer* m_VertexBuffer{};
	ID3D11ShaderResourceView* m_Texture = nullptr;
	Floor* m_floor;//�f�o�b�N�p
	Player* m_player;//�f�o�b�N�p
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	bool on = false;//�������Ƀv���C���[�Ƃ����擾���鎞�ɂ��Ă�
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};