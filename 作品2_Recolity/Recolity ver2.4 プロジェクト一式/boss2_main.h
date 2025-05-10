#pragma once
//=============================================================================
//
// �G���� [boss.h]
// Author : 
//
//=============================================================================
#ifndef _BOSS2_MAIN_H_
#define _BOSS2_MAIN_H_

#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_enemy.h"
#include "bullet_interface.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BOSS_SCALE		(5.0f)					// �{�X�X�P�[��
enum Boss2State
{
	idol,
	move,
	card_attack,
};
enum CardSclect
{
	None,
	Hook,
	Blast,
	Ball,
	FireRain,
};
//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Boss2_Main :public Base_Enemy {
private:
	Bullet_Interface* m_BulletIF;	// �o���b�g�C���^�[�t�F�[�X
	int				m_Itv_b;	// �e�̔��ˊԊu
	int				m_Itv_c;	// ��C�̔��ˊԊu
	bool				m_agro;//�퓬��������
	Boss2State     m_state;//���
	int				nomalattack;//�߂Â������̍U���N�[���^�C��
	float			idoltime;//idol��Ԃ̗h��
	int				cardattackcd;
	D3DXVECTOR2		m_MoveStatepos; //move�̍s��
	int			m_MoveStatetime; //move�̍s��
	int			m_Card_attackcelecttime;//�J�[�h�̑I��ł郂�[�V��������
	int			m_card_attacktime;//�U�����Ă鎞�Ԃ��v�����Ă�
	CardSclect m_card;
	int cd;//�e�X�g�p

	int attacksound1;
	int attacksound2;
public:
	Boss2_Main() = delete;
	Boss2_Main(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Interface* bif);
	~Boss2_Main();

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Action(void)override;
	void SearchAction(void)override;
	void StateSwap_Move(D3DXVECTOR3 pos);
	void StateSwap_Idol();
	void CardAttack();
};

#endif // !_BOSS2_MAIN_H_