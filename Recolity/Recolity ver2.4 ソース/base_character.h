//=============================================================================
//
// �L�����N�^�[���� [base_character.h]
// Author : 
//
//=============================================================================
#ifndef _BASE_CHARACTER_H_
#define _BASE_CHARACTER_H_

#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_object.h"
#include "DrawDamageDot.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
//*****************************************************************************
//	�O���錾
//*****************************************************************************
class DrawDmageDot;
//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Base_Character:public Base_Object
{
private:
	float				m_Hp;
	int				m_HitFrame;
	int				m_FootSteps; //����
	bool			m_Stuck;
	DrawDmageDot	m_DrawDotDamage;
protected:
	void SetFootSteps(int foot);
public:
	Base_Character() = default ;
	Base_Character(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, int hp, bool use);
	virtual ~Base_Character() = default;
	virtual void IsDamage(float damage);
	virtual void IsDamageDot(float damage);
	virtual void DamageAction(int frame);

	//���t�@�����X
	const float& RefHp(void) const;
	const int& RefHitFrame(void) const;
	const bool& RefStuck(void) const;
	const int& RefFootSteps(void) const;

	//�Z�b�^�[
	void SetHp(float hp);
	void SetHitFrame(int frame);
	void SetStuck(bool stuck);

	//�h�b�g�_���[�W�̐ݒ�ƍX�V�ƕ`��
	void Update_DotDamage();
	void Draw_DotDamage();
	virtual void GetFloorPos();
	virtual void Action(void) = 0;
};

#endif // !_BASE_CHARACTER_H_