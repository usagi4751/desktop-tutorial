#pragma once
#include "main.h"
//キーボードの入力と画面上のマウスの座標の取得
class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];

	static LPDIRECTINPUT8			g_pDInput;					// IDirectInput8インターフェースへのポインタ
	//--------------------------------- mouse
	static LPDIRECTINPUTDEVICE8 pMouse; // mouse
	static DIMOUSESTATE2   mouseState;		// マウスのダイレクトな状態
	static DIMOUSESTATE2   mouseTrigger;	// 押された瞬間だけON

	static XMFLOAT2 m_nowmousepointer;//現在のマウスの座標
	static bool m_DrawMouseFlag;//マウスを表示するかのフラグ
public:
	static void Init(HINSTANCE hInst, HWND hWnd);
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );

	static HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow); // マウスの初期化
	static void UninitMouse();						// マウスの終了処理
	static HRESULT UpdateMouse();					// マウスの更新処理

	//左クリック長押し
	static BOOL IsMouseLeftPressed(void)
	{
	return (BOOL)(mouseState.rgbButtons[0] & 0x80);	// 押されたときに立つビットを検査
	}
	//左クリック単押し 離すまで再入力されない
	static BOOL IsMouseLeftTriggered(void)
	{
	return (BOOL)(mouseTrigger.rgbButtons[0] & 0x80);
	}
	//右クリック長押し
	static BOOL IsMouseRightPressed(void)
	{
	return (BOOL)(mouseState.rgbButtons[1] & 0x80);
	}
	//右クリック単押し 離すまで再入力されない
	static BOOL IsMouseRightTriggered(void)
	{
	return (BOOL)(mouseTrigger.rgbButtons[1] & 0x80);
	}
	//中央クリック長押し
	static BOOL IsMouseCenterPressed(void)
	{
	return (BOOL)(mouseState.rgbButtons[2] & 0x80);
	}
	//中央クリック単押し 離すまで再入力されない
	static BOOL IsMouseCenterTriggered(void)
	{
	return (BOOL)(mouseTrigger.rgbButtons[2] & 0x80);
	}
	//サイドボタン4長押し
	static BOOL IsMouseSide4Pressed(void)
	{
		return (BOOL)(mouseState.rgbButtons[3] & 0x80);
	}
	//サイドボタン4単押し 離すまで再入力されない
	static BOOL IsMouseSide4Triggered(void)
	{
		return (BOOL)(mouseTrigger.rgbButtons[3] & 0x80);
	}
	//サイドボタン5長押し
	static BOOL IsMouseSide5Pressed(void)
	{
		return (BOOL)(mouseState.rgbButtons[4] & 0x80);
	}
	//サイドボタン5単押し 離すまで再入力されない
	static BOOL IsMouseSide5Triggered(void)
	{
		return (BOOL)(mouseTrigger.rgbButtons[4] & 0x80);
	}
	static long GetMouseX(void) { return mouseState.lX; };               // マウスがX方向に動いた相対値
	static long GetMouseY(void) { return mouseState.lY; };               // マウスがY方向に動いた相対値
	static long	 GetMouseZ(void) { return mouseState.lZ; }; ;               // マウスホイールが動いた相対値

	static XMFLOAT2 GetMousePos(void) { return m_nowmousepointer; };//現在のマウスの座標
	static void SetMousePos(XMFLOAT2 pos) { m_nowmousepointer = pos; };//マウスポインタのセット
	static void SetMouseDraw(bool flag) { m_DrawMouseFlag = flag; };//マウスを表示するか
};

