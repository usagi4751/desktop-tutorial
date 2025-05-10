/*==============================================================================

   頂点管理[polygon.h]
														 Author :
														 Date   :
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#include "main.h"
#include "renderer.h"

#define DIK_COLER_WHITE {1.0f,1.0f,1.0f,1.0f}
#define DIK_COLER_GRAY {0.6f,0.6f,0.6f,1.0f}
#define DIK_COLER_YELOW {1.5f,1.5f,0.0f,1.0f}
#define DIK_COLER_BLUE {0.2f,0.2f,1.0f,1.0f}
#define DIK_COLER_DRAKGRAY {0.2f,0.2f,0.2f,1.0f}
//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitPolygon(void);
void UninitPolygon(void);
void UpdatePolygon(void);
void DrawPolygon(void);
void SetText(std::string settext, float X, float Y, float size, D3DXCOLOR coler);
void onof(bool n);//mainでIMEONOF検知用