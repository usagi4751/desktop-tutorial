#pragma once
#pragma once
//=============================================================================
//
// �G���� [boss.h]
// Author : 
//
//=============================================================================
#ifndef _BOSS3_MAIN_H_
#define _BOSS3_MAIN_H_

#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_enemy.h"
#include "bullet_interface.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BOSS_SCALE		(5.0f)					// �{�X�X�P�[��
enum Boss3State
{
	Boss3_idol,
	Boss3_move,
	Boss3_card_attack,
};
enum Card3Sclect
{
	Boss3_None,
	Boss3_Hook,
	Boss3_Blast,
	Boss3_Ball,
	Boss3_FireRain,
};
//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Boss3_Main :public Base_Enemy {
private:
	Bullet_Interface* m_BulletIF;	// �o���b�g�C���^�[�t�F�[�X
	int				m_Itv_b;	// �e�̔��ˊԊu
	int				m_Itv_c;	// ��C�̔��ˊԊu
	bool				m_agro;//�퓬��������
	Boss3State     m_state;//���
	int				nomalattack;//�߂Â������̍U���N�[���^�C��
	float			idoltime;//idol��Ԃ̗h��
	int				cardattackcd;
	D3DXVECTOR2		m_MoveStatepos; //move�̍s��
	int			m_MoveStatetime; //move�̍s��
	int			m_Card_attackcelecttime;//�J�[�h�̑I��ł郂�[�V��������
	int			m_card_attacktime;//�U�����Ă鎞�Ԃ��v�����Ă�
	Card3Sclect m_card;
	int cd;//�e�X�g�p
public:
	Boss3_Main() = delete;
	Boss3_Main(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use, Bullet_Interface* bif);
	~Boss3_Main();

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

#endif // !_BOSS3_MAIN_H_