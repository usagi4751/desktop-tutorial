//=============================================================================
//
// �X�v���C�g���� [sprite.h]
// Author : 
//
//=============================================================================
#ifndef _SPRITE_H_
#define _SPRITE_H_
#pragma once
#include "model.h"
#include "base_object.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define UI_PRSET_UV1 D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(1.0f,1.0f)


//*****************************************************************************
// �\���̐錾
//*****************************************************************************
struct UI {	//���[�U�[�C���^�[�t�F�[�X�p�\����
	D3DXVECTOR2		m_Pos;		// ���[�U�[�C���^�[�t�F�[�X�̈ʒu
	D3DXVECTOR2		m_Scl;		// ���[�U�[�C���^�[�t�F�[�X�̑傫��(�X�P�[��)
	D3DXVECTOR2		m_Uv_v;		// ��UV�l
	D3DXVECTOR2		m_Uv_f;		// �Œ�UV�l
	D3DXCOLOR		m_Color;	// ���[�U�[�C���^�[�t�F�[�X�̃J���[
	float			m_Rot;		// ���[�U�[�C���^�[�t�F�[�X�̌���(��])
};

struct Object {	//�ȈՃI�u�W�F�N�g�p�\����
	D3DXVECTOR3		m_Pos = {0.0f,0.0f,0.0f};			// �I�u�W�F�N�g�̈ʒu
	D3DXVECTOR3		m_Rot = { 0.0f,0.0f,0.0f };			// �I�u�W�F�N�g�̈ʒu
	D3DXVECTOR3		m_Scl = { 0.0f,0.0f,0.0f };			// �I�u�W�F�N�g�̑傫��(�X�P�[��)
	D3DXVECTOR2		m_Uv_v = { 0.0f,0.0f};				// ��UV�l
	D3DXVECTOR2		m_Uv_f = { 1.0f,1.0f};				// �Œ�UV�l
	D3DXCOLOR		m_Color = { 1.0f,1.0f,1.0f,1.0f };	// �I�u�W�F�N�g�̃J���[
	MATERIAL		m_Material;	
	D3DXMATRIX		m_Mtx;								// �}�g���b�N�X

	Object() {
		m_Material.Diffuse = { 0.0f,0.0f,0.0f,1.0f };
		m_Material.Ambient = { 1.0f,1.0f,1.0f,1.0f };
		m_Material.Emission = { 0.0f,0.0f,0.0f,0.0f };
		m_Material.noTexSampling = 0;
	};
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSprite(void);
void UninitSprite(void);
void DrawNomber(D3DXVECTOR3 pos, float size, int Drawtext);
void DrawScreenCircle(D3DXVECTOR2 pos, D3DXVECTOR2 tex_pos, float radius, float rate, D3DXCOLOR color, int& tex);
void DrawScreen(UI& ui, int& tex);
void DrawScreenLT(UI& ui, int& tex);
void DrawPolygon(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f);
void DrawPolygonCR(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f);
void DrawPolygonLT(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f);
void DrawPolygonBill(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f);
void DrawPolygonBillX(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f ,float WID_X);
void DrawPolygonBillCR(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f);
void DrawPolygonBillLT(Base_Object& obj, const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f);
void DrawPolygonAnyBill(Base_Object& obj,const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f, bool InX, bool InY, bool InZ);
void DrawPolygonAnyBillCR(Base_Object& obj,const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f, bool InX, bool InY, bool InZ);
void DrawPolygonAnyBillLT(Base_Object& obj,const int& tex, const D3DXVECTOR2& uv_v, const D3DXVECTOR2& uv_f, bool InX, bool InY, bool InZ);
void Draw3DModel(Base_Object& obj, DX11_MODEL& model);

//---------------------------------
// �f�o�b�N�p
//---------------------------------
void DrawPolygon(Object& obj, const int& tex);
void DrawPolygonCR(Object& obj, const int& tex);
void DrawPolygonLT(Object& obj, const int& tex);
void DrawPolygonBill(Object& obj, const int& tex);
void DrawPolygonBillX(Object& obj, const int& tex,float WID_X);
void DrawPolygonBillXY(Object& obj, const int& tex, float WID_X, float WID_Y);
void DrawPolygonBillCR(Object& obj, const int& tex);
void DrawPolygonBillLT(Object& obj, const int& tex);
void DrawPolygonAnyBill(Object& obj, const int& tex, bool InX, bool InY, bool InZ);
void DrawPolygonAnyBillCR(Object& obj, const int& tex, bool InX, bool InY, bool InZ);
void DrawPolygonAnyBillLT(Object& obj, const int& tex, bool InX, bool InY, bool InZ);
void Draw3DModel(Object& obj, DX11_MODEL& model);


#endif // !_SPRITE_H_