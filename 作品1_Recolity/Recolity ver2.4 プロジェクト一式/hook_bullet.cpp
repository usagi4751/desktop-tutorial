#include "hook_bullet.h"
#include "main.h"
#include "input.h"
#include "camera.h"
#include "material.h"
#include "sprite.h"
#include "Game.h"
#include "floor.h"
//=====================================
// �v���C���[�ȊO�ɂ͓��Ɍ��ʂ̂Ȃ��o���b�g�ł�
// �R���W��������܂����ݒ�Ȃǂ͂ł��Ȃ��v���C���[���t�b�N���邽�߂����ɂ����ł߂���߂����O�I�ȕ��ł�
// update�œ����蔻�����Ă܂�
// �g�p�ǉ��ł��Ȃ������̂ŋ���̍�
//=====================================
Hook_Bullet::Hook_Bullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Side side,
	int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type,
	Attribute_Element att_element, int* tex, DX11_MODEL* model, float circle)
	:Base_Bullet(pos, { rot.x * -1.0f,rot.y,rot.z}, scl, vel, color, true, hook, side, damage, speed, gvt, dec, range, uv_v, uv_f, att_type, att_element, tex, model)
{
	m_pullpoint = pos;
	//�����蔻��̐ݒ�
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
Hook_Bullet::~Hook_Bullet()
{


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
//=============================================================================
// ����������
//=============================================================================
HRESULT Hook_Bullet::Init(void)
{
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void Hook_Bullet::Uninit(void)
{

}
//=============================================================================
// �X�V����
//=============================================================================
void Hook_Bullet::Update(void)
{
	Move();
	D3DXVECTOR3 Vec = GetCamera()->pos - RefPos();
	float length = D3DXVec3LengthSq(&Vec);
	D3DXVECTOR3 pull = { RefVel().x * -2.0f  ,RefVel().y * -1.0f ,RefVel().z * -2.0f };

	if (length < 300 * 300 )
	{
		GetPlayer()->IsDamage(RefDamage());
		GetPlayer()->SetVel(pull);
		GetPlayer()->effect.SetEffect(lock, low, 0);
		SetDamage(0);
		IsDiscard();
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
void Hook_Bullet::Draw(void)
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
void Hook_Bullet::Move(void)
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

	//�t���A��0�������������
	Floor_Type type = GetNowFloor(RefPos());
	if (type == Floor_Wall)
		IsDiscard();

	//�����W��0�ȉ��ɂȂ邩�A�e��y����0�ȉ��ɂȂ�����
	if (RefPos().y <= 0 || RefRange() <= 0 || RefSpeed() <= 0.01f)
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
	}
}
