#pragma once
#include"pch.h"
#define MY_MSG (WM_USER + 1)
/*#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <functional>
#include <fstream>
#include <d3d11.h>
#include <imm.h>
#pragma comment (lib, "d3d11.lib")

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment (lib, "Imm32.lib")//ImmGetContextなどを使えるように
#define DIRECTINPUT_VERSION 0x0800		// 警告対処
#include "dinput.h"

#include <DirectXMath.h>
using namespace DirectX;


#include "DirectXTex.h"
#pragma warning(disable : 4996)
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
*/
#pragma warning(disable : 4996)
#pragma comment (lib, "Ws2_32.lib")//udp




//#include <windowsx.h>//udp
//#include <winsock2.h>//udp


#pragma warning(pop)

#define SCREEN_WIDTH	(1920)
#define SCREEN_HEIGHT	(1080)
#define MAX_RECORD 64 * 1024

//HWND の取得
HWND GetWindow();

//HWND の取得
HWND GetWndprccWindow();

//謎
//void Invoke(std::function<void()> Function, int Time);


//ウィンドウのDPIの取得
float GetDPI();
//0～1のfloat型のランダムな数
float frand(void);

//D3dx9.libから持ってきた
float D3DXVec3LengthSq(XMFLOAT3* pV);

//カーソルの表示の切り替え
//flug true     カーソルの表示をなくす
//flug false    カーソルの表示をする
void SetHideCursor(bool flug);

//マウスの画面中央固定
//clip true     中央固定ON
//clip false    中央固定OFF
void MouseClip(bool clip);

//マウスポインタのウィンドウでの座標取得
XMFLOAT2 MousePos();

//文字入力をオンにして取得する
void GetInputTextString(std::string* t);
//文字入力を閉じる
void CloseInputTextString();

//2バイト文字に対応したpopback
void StdPopBack(std::string* t);

