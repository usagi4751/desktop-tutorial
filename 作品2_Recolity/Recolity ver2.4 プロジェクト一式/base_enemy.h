//=============================================================================
//
// �G���� [base_enemy.h]
// Author : 
//
//=============================================================================
#ifndef _BASE_ENEMY_H_
#define _BASE_ENEMY_H_
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_character.h"
#include "collision.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BASE_ENEMY_SCALE		(3.0f)						// �G�̊�{�X�P�[��

//*****************************************************************************
// �񋓑̐錾
//*****************************************************************************
enum Enemy_Type {	//�G�l�~�[�^�C�v
	normal_enemy = 0,
	patrol_enemy,
	bullet_enemy,
	boss_enemy,
	scorpion_enemy,
	moth_enemy,
	spider_enemy,
	total_enemy,
	boss2,
	boss3,
	none_enemy
};

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Base_Enemy:public Base_Character
{
private:
	Enemy_Type		m_Type;		// �G�l�~�[�̃^�C�v
public:
	Base_Enemy() = delete;
	Base_Enemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, int hp, Enemy_Type type);
	virtual ~Base_Enemy() = default;

	//���t�@�����X
	const Enemy_Type& RefType(void) const;
	//�Z�b�^�[
	void SetType(Enemy_Type type);

	virtual void DamageAction(int frame);
	virtual void Chase(D3DXVECTOR3 pos);
	void IsDamage(float damage)override;
	virtual void SearchAction(void);
	virtual void DistanceVolume(D3DXVECTOR3 pos);
};

#endif // !_BASE_ENEMY_H_