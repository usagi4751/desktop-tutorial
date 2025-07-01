//=============================================================================
//
// �n�ʏ��� [polygon.h]
// Author :
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
struct POLYGON
{
	D3DXVECTOR3		pos;		// �|���S���̈ʒu
	D3DXVECTOR3		rot;		// �|���S���̌���(��])
	D3DXVECTOR3		scl;		// �|���S���̑傫��(�X�P�[��)
	D3DXCOLOR		color;		// �|���S���̃J���[

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
};
enum Textsize
{
	TextSc_1 = 10,
	TextSc_2 = 15,
	TextSc_3 = 20,
	TextSc_4 = 25,
	TextSc_5 = 30,
};
//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon_Field(void);
void SetText(std::string text, D3DXVECTOR2 pos, Textsize size = TextSc_2);
