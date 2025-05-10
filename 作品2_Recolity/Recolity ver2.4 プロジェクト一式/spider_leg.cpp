//=============================================================================
//
// �G���� [spider_leg.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "spider_leg.h"
#include "material.h"
#include "sprite.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Spider_Leg::Spider_Leg(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, float len)
	:Base_Enemy(pos, rot, scl, vel, color, use, NULL, scorpion_enemy),m_Reverse(1),m_Length(len)
{

	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();	//�g�U�F
	GetMaterial()->Ambient = RefColor();	//���F
	GetMaterial()->Emission = RefColor();	//���Ȕ����F
	GetMaterial()->noTexSampling = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Spider_Leg::~Spider_Leg()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT Spider_Leg::Init(void)
{
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void Spider_Leg::Uninit(void)
{
}
//=============================================================================
// �X�V����
//=============================================================================
void Spider_Leg::Update(void)
{
	//�A�N�V����
	Action();

	//�J���[�ύX
	if (RefHitFrame() > 0) {
		SetHitFrame(RefHitFrame() - 1);
	}
	else {
		GetMaterial()->Diffuse = RefColor();	//�g�U�F
		GetMaterial()->Ambient = RefColor();	//���F
		GetMaterial()->Emission = RefColor();	//���Ȕ����F
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void Spider_Leg::Draw()
{

	// �r���f���̕`��
	Draw3DModel(*this, RefModelMaterial().m_Spider_Leg);

}
//=============================================================================
// �A�N�V����
//=============================================================================
void Spider_Leg::Action(void)
{
	SetRot({ RefRot().x + VALUE_LEG_ROTATE * m_Reverse,RefRot().y,RefRot().z });
	if (RefRot().x >= LIMIT_LEG_ANGLE || RefRot().x <= -LIMIT_LEG_ANGLE)
	{
		m_Reverse *= -1;
	}
}
