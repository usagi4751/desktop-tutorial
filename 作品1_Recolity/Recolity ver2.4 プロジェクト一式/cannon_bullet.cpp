//=============================================================================
//
// �e���� [cannon_bullet.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "cannon_bullet.h"
#include "normal_bullet_life_penetration.h"
#include "material.h"
#include "sprite.h"
#include "Game.h"
#include "floor.h"
#include "Game.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Cannon_Bullet::Cannon_Bullet(Bullet_Interface* bif, D3DXVECTOR3 pos, D3DXVECTOR3 des, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use,
	Bullet_Side side, int damage, float speed, float gvt, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type, Attribute_Element att_element, int* tex, DX11_MODEL* model, float circle)
	:Base_Bullet(pos, rot, scl, vel, color, use, cannon, side, damage, speed, gvt, NO_DEC, NULL, uv_v, uv_f, att_type, att_element, tex, model),m_Bif(bif),m_Destination(des)
{
	//�����蔻��̐ݒ�
	SetColl(new Collision(this, {0.0f,0.0f,0.0f},circle));
	m_Penetration = true;
	// �}�e���A���ݒ�
	ZeroMemory(GetMaterial(), sizeof(GetMaterial()));
	GetMaterial()->Diffuse = RefColor();
	GetMaterial()->Ambient = RefColor();
	GetMaterial()->noTexSampling = 0;

	Trajectory();
}
//=============================================================================
// �f�X�g���N�^
//=============================================================================
Cannon_Bullet::~Cannon_Bullet()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT Cannon_Bullet::Init(void)
{
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void Cannon_Bullet::Uninit(void)
{

}
//=============================================================================
// �X�V����
//=============================================================================
void Cannon_Bullet::Update(void)
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
void Cannon_Bullet::Draw(void)
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
void Cannon_Bullet::Move(void)
{
	//�e�̈ړ�
	SetPos(RefPos() + RefVel());

	//�c��̎˒�����
	SetRange((int)((float)RefRange() - (float)RefSpeed()));

	//�����Ɨ���
	SetVel({
		RefVel().x * RefDec(),
		RefVel().y + RefGvt(),
		RefVel().z * RefDec() });

	//���X�s�[�h�̒���
	SetSpeed(RefSpeed() * RefDec());

	//�����W��0�ȉ��ɂȂ邩�A�e��y����0�ȉ��ɂȂ�����
	if (RefPos().y <= 0)
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

		Attribute_Element element;
		element.m_Frame = 30;
		element.m_Interval = 10;
		element.m_Value = 0.3f;
		m_Bif->SetNBullet(life_penetration, RefSide(), { RefPos().x,1.0f,RefPos().z }, NO_VECTOR3, NO_VECTOR3,
			{ 1.0f,1.0f,1.0f,1.0f },
			RefDamage(),
			45, NO_GVT, NO_DEC, 9999999,
			fire, element,
			&RefImageMaterial().m_Cannon_Bullet, 800);
		Emitta(1, RefPos());
	}
}
//=============================================================================
// �e���v�Z
//=============================================================================
void Cannon_Bullet::Trajectory(void)
{
	D3DXVECTOR2 vecXZ = { m_Destination.x - RefPos().x,m_Destination.z - RefPos().z };
	float lenght = D3DXVec2Length(&vecXZ);
	int frame = (int)(lenght / RefSpeed());
	float height = m_Destination.y - RefPos().y * 2;
	float gravity = (2.0f * height) / (float)pow(frame, 2) - (2 * RefSpeed()) / frame;
	SetGvt(gravity);
	SetVel(D3DXVECTOR3(RefSpeed() * sinf(RefRot().y), RefSpeed(), RefSpeed() * cosf(RefRot().y)));
}