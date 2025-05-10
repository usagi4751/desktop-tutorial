//=============================================================================
//
// �G���� [base_enemy.cpp]
// Author : 
//
//=============================================================================
#include "base_enemy.h"
#include "DrawDamageDot.h"
#include "floor.h"
#include "Game.h"
#include "sound.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define HEARING_DISTANCE (2000*2000)

//=============================================================================
// �����t���R���X�g���N�^
//=============================================================================
Base_Enemy::Base_Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, int hp, Enemy_Type type)
	:Base_Character(pos, rot, scl, vel, color, hp, use), m_Type(type)
{
}

//=============================================================================
// ���t�@�����X
//=============================================================================
const Enemy_Type& Base_Enemy::RefType(void) const
{
	return m_Type;
}
//=============================================================================
// �Z�b�^�[
//=============================================================================
void Base_Enemy::SetType(Enemy_Type type)
{
	m_Type = type;
}

//=============================================================================
// �_���[�W����
//=============================================================================
void Base_Enemy::IsDamage(float damage)
{
	//�_���[�W�A�N�V����(�F�ύX)
	DamageAction(30);
	D3DXVECTOR3 pos = RefPos();
	pos.y += 150 - 30.0f + frand() * 60.0f;
	pos.x += -30.0f + frand() * 60.0f;
	pos.z += -30.0f + frand() * 60.0f;
	SetDamageText((int)damage, pos, DIK_COLER_WHITE);
	//�_���[�W�̌v�Z
	SetHp(RefHp() - damage);
	if (RefHp() <= 0)
		IsDiscard();
}
//=============================================================================
// �_���[�W���󂯂����̃A�N�V����
//=============================================================================
void Base_Enemy::DamageAction(int frame)
{
	D3DXCOLOR color = RefColor();
	color.b *= 0.3f;
	color.g *= 0.3f;
	color.a = 1.0f;
	GetMaterial()->Diffuse = color;	//�g�U�F
	GetMaterial()->Ambient =color * 0.3f;	//���F
	GetMaterial()->Emission =color * 0.3f;	//���F
	SetHitFrame(frame);
}
//=============================================================================
// �ǐ�
//=============================================================================
void Base_Enemy::Chase(D3DXVECTOR3 pos)
{
	//���K������2�_�Ԃ̍��W
	D3DXVECTOR3 vDis = pos - RefPos();
	float lenght = D3DXVec3Length(&vDis);
	vDis = D3DXVECTOR3(vDis.x / lenght, 0.0f, vDis.z / lenght);
	float floorslow = 1.0f;
	if (GetNowAdhere(RefPos()) == Floor_Water)
	{
		floorslow = 0.85f;
	}
	//�ǐՐ�Ɉړ�
	SetPos(D3DXVECTOR3(RefPos().x + vDis.x * RefVel().x * floorslow, RefPos().y, RefPos().z + vDis.z * RefVel().z * floorslow));
}
//=============================================================================
// �v���C���[�Ƃ̃A�N�V����
//=============================================================================
void Base_Enemy::SearchAction(void)
{
}
//=============================================================================
// �����ɂ�鉹�ʂ̒���
//=============================================================================
void Base_Enemy::DistanceVolume(D3DXVECTOR3 pos)
{
	//2�_�Ԃ̋�����2��l�̎擾
	D3DXVECTOR3 vec = RefPos() - pos;
	float length = D3DXVec3LengthSq(&vec);

	//�����ɂ�鉹�ʂ̒���
	if (length > HEARING_DISTANCE) {
		SetVolume(RefFootSteps(), 0);
	}
	else{
		float rate = length / HEARING_DISTANCE;
		SetVolume(RefFootSteps(), 1.0f - rate);
	}
}
