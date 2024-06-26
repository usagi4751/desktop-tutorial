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

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体宣言
//*****************************************************************************


struct Image_Material
{
	int Floor_Image[8] = { -1, -1 ,-1 ,-1 ,-1 ,-1 ,-1 ,-1 };
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void LoadMaterial(void);
void ReleaseMaterial(void);
Image_Material& RefImageMaterial(void);

#endif // !_MATERIAL_H_