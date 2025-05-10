//=============================================================================
//
// �G���� [enemy.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "normal_enemy.h"
#include "base_attribute.h"
#include "material.h"
#include "sprite.h"
#include "floor.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define HIT_POINT	(100)							// �q�b�g�|�C���g
#define COLL_CIRCLE	(100.0f)						// �����蔻��̔��a

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Normal_Enemy::Normal_Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use)
	:Base_Enemy(pos, rot, scl, vel, color, use, HIT_POINT, normal_enemy)
{

	//�����蔻��̐ݒ�
	SetColl(new Collision(this, { 0.0f,100.0f,0.0f }, 100));

	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();	//�g�U�F
	GetMaterial()->Ambient = RefColor()*0.3f;	//���F
	GetMaterial()->Emission = RefColor() * 0.3f;	//���Ȕ����F
	GetMaterial()->noTexSampling = 0;

}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Normal_Enemy::~Normal_Enemy()
{
	Uninit();
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Normal_Enemy::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void Normal_Enemy::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void Normal_Enemy::Update(void)
{
	Update_DotDamage();
	//�J���[�̕ύX
	if (RefHitFrame() > 0) {
		SetHitFrame(RefHitFrame() - 1);
	}
	else {
		SetColor({ 1.0f,1.0f,1.0f,1.0f });
		GetMaterial()->Diffuse = RefColor();	//�g�U�F
		GetMaterial()->Ambient = RefColor() * 0.3f;	//���F
		GetMaterial()->Emission = RefColor() * 0.3f;	//���Ȕ����F
		SetStuck(false);
	}
	if (GetNowAdhere(RefPos()) == Floor_flame)
	{
		IsDamageDot(3.0f /60.0f);
	}
	//�󂯂������̏���
	for (int index = 0; index < ATTRIBUTE_NUM; index++)
	{
		if (GetAttribute(index) != nullptr)
			GetAttribute(index)->AttributeByType(this);
	}
	//�t���A���ʂ̓K��
	GetFloorPos();
	//�����蔻��̍Đݒ�
	for (Collision* pColl : *GetColl())
	{
		pColl->SetCollPos();
	}
	SetOldPos();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Normal_Enemy::Draw(void)
{
	Draw3DModel(*this, RefModelMaterial().m_Normal_Enemy);
	Draw_DotDamage();
	//HP�̕\��
	Object hp;
	hp.m_Pos = { RefPos().x,RefPos().y - 20.0f + 8.7f * RefScl().y * DISTANCE_DIFF,RefPos().z };
	hp.m_Uv_v = { 0.0f + 0.5f - 0.5f * ((RefHp() / (float)HIT_POINT)),0.0f };
	hp.m_Uv_f = { 0.5f,1.0f };
	hp.m_Scl = { 150.0f ,10.0f,0.0f };
	hp.m_Color = { 1.0f,0.0f,0.0f,1.0f };
	DrawPolygonBillX(hp, RefImageMaterial().m_Hp, 0);
#if _DEBUG
	//�����蔻�苅�̐ݒ�
	Object sphere;
	for (Collision* pColl : *GetColl())
	{
		sphere.m_Pos = pColl->RefCollPos();
		sphere.m_Scl = { COLL_CIRCLE ,COLL_CIRCLE ,COLL_CIRCLE };
		sphere.m_Rot = RefRot();
		sphere.m_Color = { 5.0f ,5.0f ,5.0f,1.0f };
		Draw3DModel(sphere, RefModelMaterial().m_Sphere);
	}
	
#endif // _DEBUG

}
//=============================================================================
// �A�N�V����
//=============================================================================
void Normal_Enemy::Action(void)
{
}