#pragma once
#include "draw2d_Manager.h"
class UI_Text;
class UI_Tex;
//==================
//�{�^���@�\
//==================
class Buttun
{
private:
	XMFLOAT2 m_Pos = { 50.0f,50.0f};
	XMFLOAT2 m_Scale = { 100.0f,100.0f };
	UI_Tex m_ButtunTexture;
	bool m_Active = false;//�\�����邩

public:
	Buttun();
	void Uninit();
	//�\���[�x
	void SetDepth(float depth);
	//�F�@{R,G,B,A}
	void SetColer(XMFLOAT4 coler);
	//���W
	void SetPosition(XMFLOAT2 position);
	//�傫��
	void SetScale(XMFLOAT2 scale);
	//UV�l
	void SetUV(XMFLOAT2   uv, XMFLOAT2   UV);
	//�\�����邩
	void SetActive(bool active);
	//�e�N�X�`���̐ݒ�@�ԍ��Ō��܂�
	void SetTextuer(int textuer);
	bool OnMouseButtun();//�}�E�X�|�C���^���{�^���ɔ���Ă��邩

};

