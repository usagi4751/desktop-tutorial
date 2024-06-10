/*==============================================================================

   テクスチャの描画 [main.h]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#pragma once


#pragma warning(push)
#pragma warning(disable:4005)

#define _CRT_SECURE_NO_WARNINGS			// scanf のwarning防止
#include <stdio.h>
#include <string>
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <d3dx9.h>
#include <math.h>
#include <imm.h>
#include <string.h>
#include <WinUser.h>
#pragma comment(lib,"d2d1.lib")//テキスト表示で追加
#pragma comment(lib,"dwrite.lib")//テキスト表示で追加

#include <d2d1.h>//テキスト表示で追加
#include <dwrite.h>//テキスト表示で追加
#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"
#include "mmsystem.h"

#pragma warning(pop)


//*****************************************************************************
// ライブラリのリンク
//*****************************************************************************
#pragma comment (lib, "d3d11.lib")		
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib, "d3dx11.lib")	
#pragma comment (lib, "d3dx9.lib")	
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "dxerr.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "Imm32.lib")


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1920)				// ウインドウの幅
#define SCREEN_HEIGHT	(1080)				// ウインドウの高さ


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
float frand(void);
std::string Gettextstring();
void Gettextstringclose();
D3DXVECTOR2 GetMousePos();
int GetGameFlame();
float GeyDPI();