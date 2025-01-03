//=============================================================================
//
// ユーザーインターフェース処理 [ui.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#define UI_PRSET_UV1 D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(1.0f,1.0f)
//*****************************************************************************
// マクロ定義
//*****************************************************************************
struct UI2
{
	D3DXVECTOR2		m_Pos;		// ユーザーインターフェースの位置
	D3DXVECTOR2		m_Scl;		// ユーザーインターフェースの大きさ(スケール)
	D3DXVECTOR2		m_Uv_v;		// 可変UV値
	D3DXVECTOR2		m_Uv_f;		// 固定UV値
	D3DXCOLOR		m_Color;		// ユーザーインターフェースのカラー
	float			m_Rot;		// ユーザーインターフェースの向き(回転)
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void DrawScreen2(UI2 pol, int tex);
HRESULT InitUI(void);
void UninitUI(void);
void UpdateUI(void);
void DrawUI(void);

