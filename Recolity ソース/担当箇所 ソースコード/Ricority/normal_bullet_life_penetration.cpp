//=============================================================================
//
// �e���� [normal_bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "normal_bullet_life_penetration.h"
#include "material.h"
#include "sprite.h"
#include "Game.h"
#include "floor.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Normal_Bullet_Life_Penetration::Normal_Bullet_Life_Penetration(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, int life, D3DXCOLOR color, bool use,
	Bullet_Side side, int damage, float speed, float gvt, float dec, int range,D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type, Attribute_Element att_element, int* tex, DX11_MODEL* model, float circle)
	:Base_Bullet(pos, rot, scl, vel, color, use, bullet, side, damage, speed, gvt, dec, range, uv_v, uv_f, att_type, att_element, tex, model)
{
	m_life = life;
	m_StartRange = range;
	m_Penetration = false;
	//�����蔻��̐ݒ�
	SetColl(new Collision(this, {0.0f,0.0f,0.0f}, circle));
	// �}�e���A���ݒ�
	ZeroMemory(this->GetMaterial(), sizeof(this->GetMaterial()));
	this->GetMaterial()->Diffuse = this->RefColor();
	this->GetMaterial()->noTexSampling = 0;
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Normal_Bullet_Life_Penetration::~Normal_Bullet_Life_Penetration()
{
	Floor_Adhere ad = Floor_None;
	if (RefAttType() == fire)
	{
		ad = Floor_flame;
	}
	if (RefAttType() == water)
	{
		ad = Floor_Water;
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			SetAdhere({ RefPos().x - 100 * 2 + i * 100,RefPos().y,RefPos().z - 100 * 2 + j * 100 }, ad, 600);
		}
	}
}
//=============================================================================
// ����������
//=============================================================================
HRESULT Normal_Bullet_Life_Penetration::Init(void)
{
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void Normal_Bullet_Life_Penetration::Uninit(void)
{
}
//=============================================================================
// �X�V����
//=============================================================================
void Normal_Bullet_Life_Penetration::Update(void)
{
	Move();
	
	if (m_life > 0)
	{
		--m_life;
		
	}
	else
	{
		SetUse(false);
	}
	//�����蔻��̍Đݒ�
	for (Collision* pColl : *GetColl())
	{
		pColl->SetCollPos();
	}
}
//=============================================================================
// �`�揈��
//=============================================================================
void Normal_Bullet_Life_Penetration::Draw(void)
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
void Normal_Bullet_Life_Penetration::Move(void)
{
	//�e�̈ړ�
	this->SetPos(this->RefPos() + this->RefVel());

	//�c��̎˒�����
	this->SetRange(this->RefRange() - (int)this->RefSpeed());

	//�����Ɨ���
	this->SetVel({
		this->RefVel().x * this->RefDec(),
		this->RefVel().y * this->RefDec() - this->RefGvt(),
		this->RefVel().z * this->RefDec() });


	//�����W��0�ȉ��ɂȂ邩�A�e��y����0�ȉ��ɂȂ�����
	if (this->RefPos().y <= 0 || this->RefRange() <= 0 || this->RefSpeed() <= 0.01f)
	{
		this->SetUse(false);

		
	}
}
