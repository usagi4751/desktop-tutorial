#include "time_bom.h"
#include "main.h"
#include "input.h"
#include "camera.h"
#include "material.h"
#include "sprite.h"
#include "Game.h"
#include "floor.h"
//=====================================
// �G�ɂ͎g���܂���
// �v���C���[�ȊO�ɂ͓��Ɍ��ʂ̂Ȃ��o���b�g�ł�
// �R���W��������܂����ݒ�Ȃǂ͂ł��Ȃ��v���C���[���t�b�N���邽�߂����ɂ����ł߂���߂����O�I�ȕ��ł�
// update�œ����蔻�����Ă܂�
// �g�p�ǉ��ł��Ȃ������̂ŋ���̍�
//=====================================
Time_bom_Bullet::Time_bom_Bullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Side side,
	int damage, float speed, float gvt, float dec, int range, D3DXVECTOR2 uv_v, D3DXVECTOR2 uv_f, Attribute_Type att_type,
	Attribute_Element att_element, int* tex, DX11_MODEL* model, float circle)
	:Base_Bullet(pos, { rot.x * -1.0f,rot.y,rot.z }, scl, vel, color, true, hook, side, damage, speed, gvt, dec, range, uv_v, uv_f, att_type, att_element, tex, model)
{
	life = 90;
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
Time_bom_Bullet::~Time_bom_Bullet()
{



}
//=============================================================================
// ����������
//=============================================================================
HRESULT Time_bom_Bullet::Init(void)
{
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void Time_bom_Bullet::Uninit(void)
{

}
//=============================================================================
// �X�V����
//=============================================================================
void Time_bom_Bullet::Update(void)
{
	//�t���A��0�������������
	Floor_Type type = GetNowFloor(RefPos());
	if (type == Floor_Wall)
		IsDiscard();
	if (life > 0)
	{
		life--;
	}
	D3DXVECTOR3 Vec = GetCamera()->pos - RefPos();
	float length = D3DXVec3LengthSq(&Vec);
	if (life <= 0)
	{
		IsDiscard();
		if (length < 300 * 300)
		{
			GetPlayer()->IsDamage(RefDamage());
			SetDamage(0);

		}
		Emitta(9, this->RefPos());
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
void Time_bom_Bullet::Draw(void)
{


}
//=============================================================================
// �e�̓���
//=============================================================================
void Time_bom_Bullet::Move(void)
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
