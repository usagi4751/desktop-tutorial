//=============================================================================
//
// 地面処理 [polygon.h]
// Author :
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
struct POLYGON
{
	D3DXVECTOR3		pos;		// ポリゴンの位置
	D3DXVECTOR3		rot;		// ポリゴンの向き(回転)
	D3DXVECTOR3		scl;		// ポリゴンの大きさ(スケール)
	D3DXCOLOR		color;		// ポリゴンのカラー

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
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
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon_Field(void);
void SetText(std::string text, D3DXVECTOR2 pos, Textsize size = TextSc_2);
