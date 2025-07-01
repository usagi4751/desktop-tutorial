#pragma once
#include "main.h"

class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];

	static LPDIRECTINPUT8			g_pDInput;					// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^
	//--------------------------------- mouse
	static LPDIRECTINPUTDEVICE8 pMouse; // mouse
	static DIMOUSESTATE2   mouseState;		// �}�E�X�̃_�C���N�g�ȏ��
	static DIMOUSESTATE2   mouseTrigger;	// �����ꂽ�u�Ԃ���ON

	static XMFLOAT2 m_nowmousepointer;//���݂̃}�E�X�̍��W
	static bool m_DrawMouseFlag;//�}�E�X��\�����邩�̃t���O
public:
	static void Init(HINSTANCE hInst, HWND hWnd);
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );

	static HRESULT InitializeMouse(HINSTANCE hInst, HWND hWindow); // �}�E�X�̏�����
	static void UninitMouse();						// �}�E�X�̏I������
	static HRESULT UpdateMouse();					// �}�E�X�̍X�V����

	static BOOL IsMouseLeftPressed(void)
	{
	return (BOOL)(mouseState.rgbButtons[0] & 0x80);	// �����ꂽ�Ƃ��ɗ��r�b�g������
	}
	static BOOL IsMouseLeftTriggered(void)
	{
	return (BOOL)(mouseTrigger.rgbButtons[0] & 0x80);
	}
	static BOOL IsMouseRightPressed(void)
	{
	return (BOOL)(mouseState.rgbButtons[1] & 0x80);
	}
	static BOOL IsMouseRightTriggered(void)
	{
	return (BOOL)(mouseTrigger.rgbButtons[1] & 0x80);
	}
	static BOOL IsMouseCenterPressed(void)
	{
	return (BOOL)(mouseState.rgbButtons[2] & 0x80);
	}
	static BOOL IsMouseCenterTriggered(void)
	{
	return (BOOL)(mouseTrigger.rgbButtons[2] & 0x80);
	}
	static BOOL IsMouseSide4Pressed(void)
	{
		return (BOOL)(mouseState.rgbButtons[3] & 0x80);
	}
	static BOOL IsMouseSide4Triggered(void)
	{
		return (BOOL)(mouseTrigger.rgbButtons[3] & 0x80);
	}
	static BOOL IsMouseSide5Pressed(void)
	{
		return (BOOL)(mouseState.rgbButtons[4] & 0x80);
	}
	static BOOL IsMouseSide5Triggered(void)
	{
		return (BOOL)(mouseTrigger.rgbButtons[4] & 0x80);
	}
	static long GetMouseX(void) { return mouseState.lX; };               // �}�E�X��X�����ɓ��������Βl
	static long GetMouseY(void) { return mouseState.lY; };               // �}�E�X��Y�����ɓ��������Βl
	static long	 GetMouseZ(void) { return mouseState.lZ; }; ;               // �}�E�X�z�C�[�������������Βl

	static XMFLOAT2 GetMousePos(void) { return m_nowmousepointer; };//���݂̃}�E�X�̍��W
	static void SetMousePos(XMFLOAT2 pos) { m_nowmousepointer = pos; };//�}�E�X�|�C���^�̃Z�b�g
	static void SetMouseDraw(bool flag) { m_DrawMouseFlag = flag; };//�}�E�X��\�����邩
};

