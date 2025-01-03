//=============================================================================
//
// 絵素材処理 [material.h]
// Author : 
//
//=============================================================================
#ifndef _MATERIAL_H_
#define _MATERIAL_H_
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "model.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体宣言
//*****************************************************************************


struct Image_Material
{
	int m_cursortex;//カーソルのテクスチャ
	int m_Floor_Image_paper;//床の紙のテクスチャ
	int Floor_Image[8] = { -1, -1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 };//読み込まれた床のテクスチャ

};
struct Model_Material
{
	DX11_MODEL Yazirusi;//矢印のテクスチャ
	DX11_MODEL MapModel[64];//モデルの読み込み
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void LoadMaterial(void);
void ReleaseMaterial(void);
Model_Material& RefModelMaterial(void);
Image_Material& RefImageMaterial(void);

#endif // !_MATERIAL_H_