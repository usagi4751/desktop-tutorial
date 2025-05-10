
#pragma once
#include "main.h"
#include "effectmanager.h"
#include "base_character.h"
#include "button.h"
#include <map>
//=================================================
// *******�v���C���[�̃A�b�v�f�[�g�̌Ăяo����******
// 
// �e�p�����[�^�[�̃��Z�b�g	A	: PlayR
// ��
// �e�o�t�̍X�V				B	: PlayU
// ��
// �t���O�̃Z�b�g			C	: PlayS
// ��
// ���͏���					D	: PlayI
//=================================================

//
class PLAYER : public Base_Character
{
private:



	int m_stamina;//�X�^�~�i
	int m_noaction;//�X�^�~�i������ĂȂ�����
	int m_havecard;//�J�[�h�̎����Ă���ꏊ
	D3DXVECTOR3 m_pos;//���ݍ��W
	D3DXVECTOR3 m_oldpos;//1f�O�̃x�N�g��
	D3DXVECTOR3 m_vel;//�x�N�g��
	float m_movespeed;//���̑���
	bool m_dush;//�_�b�V�����Ă��邩
	bool m_sneak;//�X�j�[�N���Ă��邩
	bool m_wark;//�����Ă��邩
	bool m_jump;//�W�����v���Ă��邩
	bool m_nodush;//�X�^�~�i���Ȃ��Ȃ������Ƃɂ��_�b�V������
	bool m_minimap;//�~�j�}�b�v�̕\���t���O
	float m_slowness;//�v���C���[�̃X���E�̒l
	int		m_WorkSound;//�T�E���h
	int		m_DushSound;//�T�E���h
	std::map<std::string, Button> m_Button;
public:
	EFFECTMANAGER effect;
	~PLAYER(void) ;
	PLAYER();
	void SetPosX(float n) { m_pos.x = n; };
	void SetPosY(float n) { m_pos.y = n; };
	void SetPosZ(float n) { m_pos.z = n; };
	void SetVel(D3DXVECTOR3 vel);
	D3DXVECTOR3 GetPos() { return m_pos; };
	bool Get_Sneak() { return m_sneak; };
	void IsDamage(float damage) override;
	void IsDamageDot(float damage) override;
	void ClerFlug();
	virtual HRESULT Init(void)	override;
	virtual void Uninit(void)	 override ;
	virtual void Update(void)	override;
	virtual void Draw(void)		override;
	virtual void Draw2D(void) ;
	virtual void Action(void) override{};
	void PlayU_Vel();//�v���C���[�̃x�N�g�����v�Z�����

	void Playerstatusview();//�X�e�[�^�X��������
	void PlayerHeal(float heal);

	void PlayerDrawUi();

	void PlayR_Stamina();//�X�^�~�i�̍X�V
	void PlayR_StateUpdate();//�v���C���[�̏�Ԃ̍X�V
	void PlayR_PosUpdate();//���W�̍X�V
	void PlayU_EffectUpdate();//�G�t�F�N�g�̍X�V

	void PlayS_Dush();//�_�b�V��
	void PlayS_sneak();//�X�j�[�N
	void PlayI_Move();//�v���C���[���ړ��ł���悤�ɂȂ�
	void PlayI_FlorEffect();//������̌���
};



