//=============================================================================
//
// �G���� [moth_wing.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "moth_wing.h"
#include "material.h"
#include "sprite.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Moth_Wing::Moth_Wing(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Wing_LR lr, float len)
	:Base_Enemy(pos, rot, scl, vel, color, use, NULL, moth_enemy),m_LR(lr),m_Length(len)
{
	if (lr == w_left)
		m_Reverse = 1;
	else
		m_Reverse = -1;

	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();	//�g�U�F
	GetMaterial()->Ambient = RefColor();	//���F
	GetMaterial()->Emission = RefColor();	//���Ȕ����F
	GetMaterial()->noTexSampling = 0;
}
//=============================================================================
// ����������
//=============================================================================
HRESULT Moth_Wing::Init(void)
{
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void Moth_Wing::Uninit(void)
{
}
//=============================================================================
// �X�V����
//=============================================================================
void Moth_Wing::Update(void)
{
	//�A�N�V����
	Action();
}
//=============================================================================
// �`�揈��
//=============================================================================
void Moth_Wing::Draw(void)
{
	//�����f���̕`��
	if (m_LR == w_left)
		Draw3DModel(*this, RefModelMaterial().m_Moth_WingL);
	if (m_LR == w_right)
		Draw3DModel(*this, RefModelMaterial().m_Moth_WingR);
}
//=============================================================================
// �A�N�V����
//=============================================================================
void Moth_Wing::Action(void)
{
	SetRot({ RefRot().x  ,RefRot().y + VALUE_LEG_ROTATE * m_Reverse,RefRot().z });
	if (RefRot().y >= LIMIT_LEG_ANGLE || RefRot().y <= -LIMIT_LEG_ANGLE)
	{
		m_Reverse *= -1;
	}
}
