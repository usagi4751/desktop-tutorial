//=============================================================================
//
// �e���� [normal_bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "normal_bullet.h"
#include "material.h"
#include "sprite.h"
#include "Game.h"
#include "floor.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COLL_CIRCLE	(100.0f)

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Normal_Bullet::Normal_Bullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use,
	Bullet_Side side, int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type, Attribute_Element att_element, int* tex, DX11_MODEL* model, float circle)
	:Base_Bullet(pos, rot, scl, vel, color, use, bullet, side, damage, speed, gvt, dec, range, uv_v, uv_f, att_type, att_element, tex, model)
{
	//�����蔻��̐ݒ�
	SetColl(new Collision(this, {0.0f,0.0f,0.0f}, circle));
	m_Penetration = true;
	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = RefColor();
	GetMaterial()->Emission = RefColor();
	GetMaterial()->noTexSampling = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Normal_Bullet::~Normal_Bullet()
{

}
//=============================================================================
// ����������
//=============================================================================
HRESULT Normal_Bullet::Init(void)
{
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void Normal_Bullet::Uninit(void)
{

}
//=============================================================================
// �X�V����
//=============================================================================
void Normal_Bullet::Update(void)
{
	Move();

	//�����蔻��̍Đݒ�
	for (Collision* pColl : *GetColl())
	{
		pColl->SetCollPos();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void Normal_Bullet::Draw(void)
{
	if (GetModelId() != nullptr)
	{
		Draw3DModel(*this, *GetModelId());
	}
	else
	{
		DrawPolygonBill(*this, RefTexId(), RefUv_v(), RefUv_f());
	}

	
}
//=============================================================================
// �e�̓���
//=============================================================================
void Normal_Bullet::Move(void)
{

	//�e�̈ړ�
	SetPos(RefPos() + RefVel());

	//�c��̎˒�����
	SetRange(RefRange() - RefSpeed());

	//�����Ɨ���
	SetVel({
		RefVel().x * RefDec(),
		RefVel().y - RefGvt(),
		RefVel().z * RefDec() });

	//���X�s�[�h�̒���
	SetSpeed(RefSpeed() * RefDec());


	//�����W��0�ȉ��ɂȂ邩�A�e��y����0�ȉ��ɂȂ�����
	//�t���A��0�������������
	Floor_Type type = GetNowFloor(RefPos());
	if (RefPos().y <= 0 || RefRange() <= 0 || RefSpeed() <= 0.01f|| type == Floor_Wall)
	{
		IsDiscard();
		Floor_Adhere ad = Floor_None;
		if (RefAttType() == fire)
		{
			 ad = Floor_flame;
		}
		if (RefAttType() == water)
		{
			 ad = Floor_Water;
		}
		SetAdhere(RefPos(), ad, 600);

		if (RefAttType() == fire)
		{
			Emitta(0, this->RefPos());
		}
		if (RefAttType() == water)
		{
			for (int i = 0; i < 5; i++)
			{
				Emitta(4, this->RefPos());
			}

		}
		if (RefAttType() == wind)
		{
			Emitta(5, this->RefPos());
		}
	}
}
