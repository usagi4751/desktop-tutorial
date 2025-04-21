#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS//udpで追加
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN//udpで追加
#define NOMINMAX
#define DIRECTINPUT_VERSION 0x0800		// 警告対処



#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <functional>
#include <fstream>
#include <d3d11.h>
#include <imm.h>
#include <winsock.h>


#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment (lib, "Imm32.lib")//ImmGetContextなどを使えるように

#include "dinput.h"


#include <DirectXMath.h>


//$(SolutionDir)../../Microsoft DirectX SDK % 28June 2010 % 29\Lib\x64
using namespace DirectX;
#include "DirectXTex.h"

#pragma warning(disable:4005)
#pragma comment(lib,"d2d1.lib")//テキスト表示で追加
#pragma comment(lib,"dwrite.lib")//テキスト表示で追加
#include <string>//テキスト表示で追加
#include <string.h>//テキスト表示で追加
#include <d2d1.h>//テキスト表示で追加
#include <dwrite.h>//テキスト表示で追加
#if _DEBUG
#pragma comment(lib,"DirectXTex_Debug.lib")
#else
#pragma comment(lib,"DirectXTex_Release.lib")
#endif
#pragma comment (lib, "winmm.lib")
