//=============================================================================
//
// �G���� [bullet_enemy.h]
// Author : 
//
//=============================================================================
#ifndef _BULLET_ENEMY_H_
#define _BULLET_ENEMY_H_

#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_enemy.h"
#include "bullet_interface.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
//m_Itv_b��0��������˒��������ꍇbullet_motion���n�܂�m_Itv_b�ɔ��ˊԊu���������
//bullet_motion���K��l���܂�����e�����˂����
class Bullet_Enemy :public Base_Enemy {
private:
	Bullet_Interface*	m_BulletIF;	// �o���b�g�C���^�[�t�F�[�X
	int					m_Itv_b;	// �e�̔��ˊԊu
	int					m_bullet_motion;//�e�̔��˃��[�V�����^�C�}�[
	bool				m_trigger;//���˃g���K�[
	float				m_animationtimer;//�A�j���[�V�����̃^�C�}�[
	int					m_BulletSound;
	int					m_ChargeSound;
public:
	Bullet_Enemy() = delete;
	Bullet_Enemy
	(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Interface* bif);
	~Bullet_Enemy();

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Action(void)override;
	void SearchAction(void)override;
	void DistanceVolume(D3DXVECTOR3 pos) override;
};

#endif // !_BULLET_ENEMY_H_