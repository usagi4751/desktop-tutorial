//=============================================================================
//
// �G���� [scorpion_tail.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "scorpion_tail.h"
#include "material.h"
#include "sprite.h"
#include "Game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_DAMAGE	(10)							// �ʏ�e�̃_���[�W��
#define BULLET_SCALE	{30,30,30}						// �ړ���
#define BULLET_SPEED	(30.0f)						// �ړ���
#define BULLET_RANGE	(2500)						// �˒�����
#define SHOT_INTERVAL	(210)						// �ˌ��C���^�[�o��

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Scorpion_Tail::Scorpion_Tail(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, float len, Bullet_Interface* pBif)
	:Base_Enemy(pos, rot, scl, vel, color, use, NULL, scorpion_enemy),m_Reverse(1),m_Length(len),m_BulletIF(pBif),m_Itv_b(SHOT_INTERVAL)
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
Scorpion_Tail::~Scorpion_Tail()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT Scorpion_Tail::Init(void)
{
	return S_OK;
}
//=============================================================================
// �I������
//=============================================================================
void Scorpion_Tail::Uninit(void)
{
}
//=============================================================================
// �X�V����
//=============================================================================
void Scorpion_Tail::Update(void)
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
void Scorpion_Tail::Draw(void)
{
	// �K�����f���̕`��
	Draw3DModel(*this, RefModelMaterial().m_Scorpion_Tail);

}
//=============================================================================
// �A�N�V����
//=============================================================================
void Scorpion_Tail::Action(void)
{
	SetRot({ RefRot().x + VALUE_TAIL_ROTATE * m_Reverse,RefRot().y,RefRot().z });
	if (RefRot().x >= LIMIT_TAIL_ANGLE || RefRot().x <= -LIMIT_TAIL_ANGLE)
	{
		m_Reverse *= -1;
	}
}
//=============================================================================
// �v���C���[�Ƃ̃A�N�V����
//=============================================================================
void Scorpion_Tail::SearchAction(void)
{
	SetRot({ 0.0f,RefRot().y,RefRot().z });
	// �e�̔���
	m_Itv_b--;
	if (m_Itv_b >= 30 && m_Itv_b <= 50) {
		D3DXVECTOR3 pos = D3DXVECTOR3(RefPos().x + 20.0f * DISTANCE_DIFF * sinf(RefRot().y),
			RefPos().y + (RefScl().y + 1.0f * DISTANCE_DIFF),
			RefPos().z + 20.0f * DISTANCE_DIFF * cosf(RefRot().y));
		Emitta(6, pos);
	}
	if (m_Itv_b <= 0)
	{
		//�e�̔��ˈʒu
		D3DXVECTOR3 pos = D3DXVECTOR3(RefPos().x + 20.0f * DISTANCE_DIFF * sinf(RefRot().y),
			RefPos().y + (RefScl().y + 2.0f * DISTANCE_DIFF),
			RefPos().z + 20.0f * DISTANCE_DIFF * cosf(RefRot().y));

		//�e�̔��ˑ��x
		D3DXVECTOR3 vel = D3DXVECTOR3(BULLET_SPEED * sinf(RefRot().y), 0.0f, BULLET_SPEED * cosf(RefRot().y));

		Attribute_Element element;
		element.m_Frame = 300;
		element.m_Interval = 6;
		element.m_Value = 0.1f;

		m_BulletIF->SetNBullet(bullet, enemy, pos, RefRot(), BULLET_SCALE, { 1.0f,1.0f,1.0f,1.0f }, BULLET_DAMAGE,
			BULLET_SPEED, NO_GVT, NO_DEC, BULLET_RANGE, fire, element, &RefImageMaterial().m_sasori_bullet);
		m_Itv_b = SHOT_INTERVAL;
	}
}
