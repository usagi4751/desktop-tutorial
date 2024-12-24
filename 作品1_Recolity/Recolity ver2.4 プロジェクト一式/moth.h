//=============================================================================
//
// �G���� [moth.h]
// Author : 
//
//=============================================================================
#ifndef _MOTH_H_
#define _MOTH_H_
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "base_enemy.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOTH_SCALE		(60.0f)						// �K�̃X�P�[��
#define MOTH_WING_NUM	(2)							// ���̐�
#define MOTH_ANGLE	(D3DXToRadian(0.0f))			// �K�̊p�x

//*****************************************************************************
// �N���X�錾
//*****************************************************************************
class Moth :public Base_Enemy {
private:
	Base_Enemy* m_Wing[MOTH_WING_NUM];
	int m_SoundIndex;
public:
	Moth() = delete;
	Moth
	(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scl, D3DXVECTOR3 vel, D3DXCOLOR color, bool use);
	~Moth();

	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Action(void)override;
};

#endif // !_MOTH_H_