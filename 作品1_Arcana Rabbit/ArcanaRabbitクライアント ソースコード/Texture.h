#pragma once
#include "main.h"
#include "renderer.h"

//======================
//テクスチャの読み込み機能
//======================

//読み込み
int LoadTexture(const wchar_t* fileName);

//リリース
void UninitTexture(void);

//呼び出し
ID3D11ShaderResourceView** GetTexture(int index);
