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
#include "winuser.h"
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


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SCREEN_WIDTH	(1920)				// ウインドウの幅
#define SCREEN_HEIGHT	(1080)				// ウインドウの高さ

enum
{
    LibCur_ARROW = 0,
    LibCur_IBEAM = 1,
    LibCur_WAIT = 2,
    LibCur_CROSS = 3,
    LibCur_UPARROW = 4,
    LibCur_SIZE = 128,
    LibCur_ICON,
    LibCur_SIZENWSE,
    LibCur_SIZENESW,
    LibCur_SIZEWE,
    LibCur_SIZENS,
    LibCur_SIZEALL,
    LibCur_NO,
    LibCur_HAND,
    LibCur_APPSTARTING,
    LibCur_HELP


};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//ランダム作成0-1の間
float frand(void);
HWND GetHwnd(void);